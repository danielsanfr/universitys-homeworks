package projects.timeseries;

import jsensor.nodes.messages.Packet;
import jsensor.nodes.models.ReliabilityModel;

public class ReliableDelivery extends ReliabilityModel {

	@Override
	public boolean reachesDestination(Packet packet) {
		return false;
	}

}
