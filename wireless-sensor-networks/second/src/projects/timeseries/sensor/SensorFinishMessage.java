package projects.timeseries.sensor;

import jsensor.nodes.messages.Message;
import projects.timeseries.sink.SinkNode;

public class SensorFinishMessage extends Message {
	
	private static long id = -1;

	private final SensorNode sender;
	private final SinkNode destination;

	public SensorFinishMessage(SensorNode sender, SinkNode destination) {
		this(++id, sender, destination);
	}

	private SensorFinishMessage(long id, SensorNode sender, SinkNode destination) {
		super();
		setID(id);
		this.sender = sender;
		this.destination = destination;
	}

	@Override
	public Message clone() {
		return new SensorFinishMessage(getID(), sender, destination);
	}
	
	public SensorNode getSender() {
		return sender;
	}
	
	public SinkNode getDestination() {
		return destination;
	}

	@Override
	public String toString() {
		return "SensorFinishMessage [getID()=" + getID() + ", sender=" + sender + ", destination=" + destination + "]";
	}

}
