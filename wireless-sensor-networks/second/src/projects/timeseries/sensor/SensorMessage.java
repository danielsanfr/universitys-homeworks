package projects.timeseries.sensor;

import jsensor.nodes.messages.Message;
import projects.timeseries.sink.SinkNode;

public class SensorMessage extends Message {

	private static long id = -1;

	private final int hops;
	private final float value;
	private final SensorNode sender;
	private final SinkNode destination;
	
	public SensorMessage(float value, int hops, SensorNode sender, SinkNode destination) {
		this(++id, value, hops, sender, destination);
	}
	
	private SensorMessage(long id, float value, int hops, SensorNode sender, SinkNode destination) {
		super();
		setID(id);
		this.hops = hops;
		this.value = value;
		this.sender = sender;
		this.destination = destination;
	}

	@Override
	public Message clone() {
		return new SensorMessage(getID(), value, hops, sender, destination);
	}

	public float getValue() {
		return value;
	}

	public SensorNode getSender() {
		return sender;
	}

	public SinkNode getDestination() {
		return destination;
	}

	public int getHops() {
		return hops;
	}


	@Override
	public String toString() {
		return "SensorMessage [getID()=" + getID() + ", hops=" + hops + ", value=" + value + ", sender=" + sender
				+ ", destination=" + destination + "]";
	}

}
