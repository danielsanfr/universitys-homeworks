package projects.timeseries;

import jsensor.nodes.Node;
import jsensor.nodes.models.DistributionModelNode;
import jsensor.utils.Position;
import projects.timeseries.sink.SinkNode;

public class TimeSerieDistribution extends DistributionModelNode {

	@Override
	public Position getPosition(Node node) {
		final Position position;
		if (node instanceof SinkNode) {
			position = new Position(node.getID() * 100, 10);
		} else {
			int mult = 1;
			for (int i = node.getID(); i > 4; i -= 4, ++mult) { }
			int sinkId = (node.getID() % 4);
			if (sinkId == 0) sinkId = 4;
			position = new Position(sinkId * 100 , mult * 10);
		}
		return position;
	}

}
