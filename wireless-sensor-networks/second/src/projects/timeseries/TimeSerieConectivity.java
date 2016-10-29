package projects.timeseries;

import jsensor.nodes.Node;
import jsensor.nodes.models.ConnectivityModel;

public class TimeSerieConectivity extends ConnectivityModel {

	@Override
	public boolean isConnected(Node node1, Node node2) {
		return checkConnectivy(node1, node2);
	}

	@Override
	public boolean isNear(Node node1, Node node2) {
		return checkConnectivy(node1, node2);
	}

	private boolean checkConnectivy(Node node1, Node node2) {
		return node1.getPosition().getPosX() == node2.getPosition().getPosX();
	}

}
