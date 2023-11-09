package jni;

import java.util.Vector;

public class Athlete extends Competitor{

	private int id;
	
	public int numberOfPlayers() {
		return 1;
	}
	
	public Athlete(Games games, Country country, Sport sport, String discipline, String type, String medal, int id) {
		super(games, country, sport, discipline, type, medal);
		this.id = id;
	}
	
	public Vector<Integer> getPlayerIds(){
		Vector<Integer> result = new Vector<>();
		result.add(id);
		return result;
	}
}
