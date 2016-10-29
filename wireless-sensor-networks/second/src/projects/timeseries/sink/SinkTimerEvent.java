package projects.timeseries.sink;

import jsensor.nodes.events.TimerEvent;
import jsensor.runtime.Jsensor;
import projects.timeseries.sensor.SensorNode;
import projects.timeseries.sink.SinkMessage.TransmitionHops;

public class SinkTimerEvent extends TimerEvent {

	@Override
	public void fire() {
		final int hops;
		final SinkMessage.TransmitionHops transmitionHops;
		switch (node.getID()) {
			case 4:
				hops = 5;
				transmitionHops = TransmitionHops.RAMDOM_HOPS;
				break;
			case 3:
				hops = 10;
				transmitionHops = TransmitionHops.RAMDOM_HOPS;
				break;
			case 2:
				hops = 5;
				transmitionHops = TransmitionHops.FIXED_HOPS;
				break;
			case 1:
			default:
				hops = 10;
				transmitionHops = TransmitionHops.FIXED_HOPS;
				break;
		}

		SensorNode sensorNode;
		for (int idOffset = 4; idOffset <= 16; idOffset += 4) {
			sensorNode = (SensorNode) Jsensor.getNodeByID(node.getID() + idOffset);
			node.multicast(new SinkMessage(hops, transmitionHops, (SinkNode) node, sensorNode));
		}
	}

}
