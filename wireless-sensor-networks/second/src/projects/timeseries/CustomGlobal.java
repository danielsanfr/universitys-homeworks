package projects.timeseries;

import jsensor.runtime.AbsCustomGlobal;
import jsensor.runtime.Jsensor;

public class CustomGlobal extends AbsCustomGlobal {

	@Override
	public boolean hasTerminated() {
		return false;
	}

	@Override
	public void postRound() {
	}

	@Override
	public void postRun() {
	}

	@Override
	public void preRound() {
	}

	@Override
	public void preRun() {
		System.out.println(Jsensor.getNumNodes("SinkNode"));
	}

}
