package projects.timeseries;

import jsensor.nodes.Node;
import jsensor.nodes.messages.Message;
import jsensor.nodes.models.MessageTransmissionModel;

public class DefaultMessageTransmissionModel extends MessageTransmissionModel {

	@Override
	public float timeToReach(Node node1, Node node2, Message message) {
		return 5;
	}

}
