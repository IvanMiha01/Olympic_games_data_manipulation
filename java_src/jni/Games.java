package jni;

import java.util.Vector;

public class Games {

	private int year;
	private String period;
	private String city;
	private Vector<Competitor> competitors = new Vector<>();
	
	public Games(int year, String period, String city){
		this.year = year;
		this.period = period;
		this.city = city;
	}

	public int getYear() {
		return year;
	}

	public String getPeriod() {
		return period;
	}

	public String getCity() {
		return city;
	}

	public Vector<Competitor> getCompetitors() {
		return competitors;
	}
	
	
	
}
