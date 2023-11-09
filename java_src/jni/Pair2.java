package jni;

public class Pair2 {

	private Integer first;
	private String second;
	
	public Pair2(Integer first, String second) {
		this.first = first;
		this.second = second;
	}
	
	public Integer getFirst() {
		return first;
	}
	
	public String getSecond() {
		return second;
	}
	
	@Override
	public String toString() {
		return first + " " + second;
	}
}
