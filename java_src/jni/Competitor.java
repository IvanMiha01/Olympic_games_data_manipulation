package jni;

import java.util.Vector;

public class Competitor {

	private Games games;
	private Country country;
	private Sport sport;
	private String discipline;
	private String type;
	private String medal;
	
	public Competitor(Games games, Country country, Sport sport, String discipline, String type, String medal) {
		this.games = games;
		this.country = country;
		this.sport = sport;
		this.discipline = discipline;
		this.type = type;
		this.medal = medal;
	}
	
	public int numberOfPlayers() {
		return 0;
	}
	
	public Vector<Integer> getPlayerIds(){
		return new Vector<Integer>();
	}

	public Games getGames() {
		return games;
	}

	public Country getCountry() {
		return country;
	}

	public Sport getSport() {
		return sport;
	}

	public String getDiscipline() {
		return discipline;
	}

	public String getType() {
		return type;
	}

	public String getMedal() {
		return medal;
	}
	
	
}
