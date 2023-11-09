package jni;

import java.util.Vector;

public class Sport {

	private String name;
	private Vector<Competitor> competitors = new Vector<>();
	
	public Sport(String name) {
		this.name = name;
	}
	
	public Vector<Competitor> getCompetitors(){
		return competitors;
	}
}
