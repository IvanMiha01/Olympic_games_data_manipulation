package jni;

public class Pair{

	private String first;
	private Integer second;
	
	public Pair(String first, Integer second) {
		this.first = first;
		this.second = second;
	}
	
	public String getFirst() {
		return first;
	}
	
	public Integer getSecond() {
		return second;
	}
	
	@Override
	public String toString() {
		return first + " " + second;
	}
}
