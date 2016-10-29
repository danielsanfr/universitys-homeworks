package projects.timeseries.sensor;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

import jsensor.nodes.Node;
import jsensor.nodes.messages.Inbox;
import jsensor.nodes.messages.Message;
import jsensor.runtime.Jsensor;
import projects.timeseries.sink.SinkMessage;
import projects.timeseries.sink.SinkMessage.TransmitionHops;
import projects.timeseries.sink.SinkNode;

public class SensorNode extends Node {

	private static final Deque<Float> globalTimeSerie;
	static {
		globalTimeSerie = new LinkedList<>();
		BufferedReader bufferedReader = null;
		try {
			String currentLine;
			bufferedReader = new BufferedReader(new FileReader("annual.csv"));
			while ((currentLine = bufferedReader.readLine()) != null) {
				globalTimeSerie.add(Float.valueOf(currentLine));
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (bufferedReader != null) bufferedReader.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}

	private int hops;
	private int hopsCount;
	private Deque<Float> timeSerie;
	private List<Long> messagesIds;
	private boolean firstTime = true;
	private float transmitionProbability;
	private TransmitionHops transmitionHops;

	@Override
	public void onCreation() {
		messagesIds = new ArrayList<>();
		timeSerie = new LinkedList<>(globalTimeSerie);
	}

	@Override
	public void handleMessages(Inbox inbox) {
		while (inbox.hasMoreMessages()) {
			final Message message = inbox.getNextMessage();
			if (messagesIds.contains(message.getID())) continue;

			messagesIds.add(message.getID());
			if (message instanceof SinkMessage) {
				final SinkMessage sinkMessage = (SinkMessage) message;
				if (sinkMessage.getDestination().equals(this)) {
					hops = sinkMessage.getHops();
					transmitionProbability = getRandom().nextFloat();
					transmitionHops = sinkMessage.getTransmitionHops();
					new SensorTimerEvent().startRelative(1, this);
					return;
				}
			}
			multicast(message);
		}
	}
	
	@Override
	public String toString() {
		return "SensorNode [ID=" + ID + "]";
	}

	public boolean hasNextMessage() {
		return !timeSerie.isEmpty();
	}

	public float getNextMessage() {
		return timeSerie.poll();
	}

	public void executeActionIfNeeded(SensorTimerEvent sensorTimerEvent, SinkNode destination) {
		final float value = timeSerie.poll();

		if (firstTime) {
			firstTime = false;
			multicast(new SensorMessage(value, 0, this, destination));
		} else if (hopsCount >= hops) {
			hopsCount = 0;
			multicast(new SensorMessage(value, hops, this, destination));
		} else if (SinkMessage.TransmitionHops.RAMDOM_HOPS.equals(transmitionHops)
				&& getRandom().nextFloat() > transmitionProbability) {
			multicast(new SensorMessage(value, hopsCount, this, destination));
			hopsCount = 0;
		} else {
			++hopsCount;
		}
		if (!timeSerie.isEmpty()) {
			sensorTimerEvent.startRelative(1, this);
		} else {
			final SensorFinishMessage sensorFinishMessage = new SensorFinishMessage(this, destination);
			Jsensor.log("sendTime: " + Jsensor.currentTime + "\t message: " + sensorFinishMessage);
			multicast(sensorFinishMessage);
		}
	}

}
