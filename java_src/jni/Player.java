package jni;

public class Player {

	private int id;
	private String name;
	private String gender;
	private int years;
	private double height;
	private double weight;

	public Player(int id, String name, String gender, int years, double height, double weight) {
		this.id = id;
		this.name = name;
		this.gender = gender;
		this.years = years;
		this.height = height;
		this.weight = weight;
	}
	
	public double getHeight() {
	    return height;
	}

	public double getWeight() {
		return weight;
	}

	public int getYears() {
		return years;
	}
}
