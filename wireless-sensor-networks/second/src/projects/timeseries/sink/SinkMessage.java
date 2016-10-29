package projects.timeseries.sink;

import jsensor.nodes.messages.Message;
import projects.timeseries.sensor.SensorNode;

public class SinkMessage extends Message {

	public enum TransmitionHops{
		RAMDOM_HOPS,
		FIXED_HOPS
	}

	private static long id = -1;

	private final int hops;
	private final SinkNode sender;
	private final SensorNode destination;
	private final TransmitionHops transmitionHops;
	
	public SinkMessage(int hops, TransmitionHops transmitionHops, SinkNode sender, SensorNode destination) {
		this(++id, hops, transmitionHops, sender, destination);
	}
	
	private SinkMessage(long id, int hops, TransmitionHops transmitionHops, SinkNode sender, SensorNode destination) {
		super();
		setID(id);
		this.hops = hops;
		this.sender = sender;
		this.destination = destination;
		this.transmitionHops = transmitionHops;
	}

	@Override
	public Message clone() {
		return new SinkMessage(getID(), hops, transmitionHops, sender, destination);
	}

	public int getHops() {
		return hops;
	}

	public SinkNode getSender() {
		return sender;
	}

	public SensorNode getDestination() {
		return destination;
	}

	public TransmitionHops getTransmitionHops() {
		return transmitionHops;
	}

	@Override
	public String toString() {
		return "SinkMessage [getID()=" + getID() + ", hops=" + hops + ", sender=" + sender
				+ ", destination=" + destination + ", transmitionHops=" + transmitionHops + "]";
	}

}
