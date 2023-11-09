package jni;

import java.util.Vector;

public class Team extends Competitor{

	private Vector<Integer> ids;
	
	public Team(Games games, Country country, Sport sport, String discipline, String type, String medal, Vector<Integer> ids) {
		super(games, country, sport, discipline, type, medal);
		this.ids = ids;
	}
	
	@Override
	public Vector<Integer> getPlayerIds() {
		return ids;
	}
}
