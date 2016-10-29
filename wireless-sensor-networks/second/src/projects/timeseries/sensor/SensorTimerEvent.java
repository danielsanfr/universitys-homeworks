package projects.timeseries.sensor;

import jsensor.nodes.events.TimerEvent;
import jsensor.runtime.Jsensor;
import projects.timeseries.sink.SinkNode;

public class SensorTimerEvent extends TimerEvent {

	@Override
	public void fire() {
		final int destId = (node.getID() % 4);
		final SinkNode destination = (SinkNode) Jsensor.getNodeByID(((destId == 0) ? 4 : destId));

//		boolean loop = true;
//		while (loop) {
//			FIXME: The getRandomNode method never returns the node 4
//			SinkNode dest = (SinkNode) node.getRandomNode("SinkNode");
//			if (dest == null) continue;
//
//			for (int i = 4; i <= 16; i += 4) {
//				if (dest.getID() + i == node.getID()) {
//					loop = false;
//					break;
//				}
//			}
//		}

		((SensorNode) node).executeActionIfNeeded(this, destination);
	}

}
