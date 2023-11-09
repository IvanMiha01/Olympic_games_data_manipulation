package jni;

import java.util.Vector;

public class Country {

	private String name;
	private Vector<Competitor> competitors = new Vector<>();
	
	public Country(String name) {
		this.name = name;
	}
	public Vector<Competitor> getCompetitors() {
		return competitors;
	}
	public String getName() {
		return name;
	}
}
