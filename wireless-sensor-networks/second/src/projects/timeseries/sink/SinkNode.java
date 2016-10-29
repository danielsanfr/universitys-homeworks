package projects.timeseries.sink;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import jsensor.nodes.Node;
import jsensor.nodes.messages.Inbox;
import jsensor.nodes.messages.Message;
import jsensor.runtime.Jsensor;
import projects.timeseries.sensor.SensorFinishMessage;
import projects.timeseries.sensor.SensorMessage;

public class SinkNode extends Node {

	private List<Long> messagesIds;
	private Map<Integer, List<Float>> datas;
	private Map<Integer, Integer> realDataCount;
	
	@Override
	public void onCreation() {
		datas = new HashMap<>();
		realDataCount = new HashMap<>();
		messagesIds = new ArrayList<>();

		new SinkTimerEvent().startRelative(1, this);
	}

	@Override
	public void handleMessages(Inbox inbox) {
		while (inbox.hasMoreMessages()) {
			final Message message = inbox.getNextMessage();
			if (messagesIds.contains(message.getID())) continue;

			messagesIds.add(message.getID());
			if (message instanceof SensorMessage) {
				handlerSensorMessage((SensorMessage) message);
			} else if (message instanceof SensorFinishMessage) {
				handlerSensorFinishMessage((SensorFinishMessage) message);
			}
		}
	}

	@Override
	public String toString() {
		return "SinkNode [ID=" + ID + "]";
	}

	private void handlerSensorMessage(final SensorMessage message) {
		if (message.getDestination().equals(this)) {
			final int senderId = message.getSender().getID();
			List<Float> data = datas.get(senderId);
			if (data == null) {
				data = new ArrayList<>();
				datas.put(senderId, data);
				realDataCount.put(senderId, 0);
			}

			final float newValue = message.getValue();
			if (!data.isEmpty()) {
				final float lastValue = data.get(data.size() - 1);
				for (int i = 0; i < message.getHops(); i++) {
					data.add(randValue(lastValue, newValue));
				}
			}
			data.add(newValue);
			realDataCount.put(senderId, realDataCount.get(senderId) + 1);
		} else {
			multicast(message);
		}
	}

	private void handlerSensorFinishMessage(SensorFinishMessage message) {
		Jsensor.log("receiveTime: " + Jsensor.currentTime + "\t message: " + message);
		final BufferedWriter bufferedWriter;
		try {
			final int senderId = message.getSender().getID();
			final List<Float> data = datas.remove(senderId);
			if (data == null) return;

			System.out.println(String.format("%d received %d values from %d", ID, realDataCount.get(senderId), senderId));
			bufferedWriter = new BufferedWriter(new FileWriter(new File(String.format("Results/sink-%d/node-%d.csv", ID, senderId))));
			for (Float value : data) {
				bufferedWriter.write(String.format("%.4f\n", value));
			}
			bufferedWriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private float randValue(float a, float b) {
	    boolean flag = true;
	    float min, max, rand;
	    if (a == b) {
	    	return a;
	    } else if (a > b) {
	        max = a;
	        min = b;
	    } else {
	        max = b;
	        min = a;
	    }
	    do {
	        rand = getRandom().nextFloat();
	        if (rand >= min && rand <= max) {
	            flag = false;
	        } else {
	            rand = -1*rand;
	            if (rand >= min && rand <= max)
	                flag = false;
	        }
	    } while (flag);
	    return rand;
	}

}
