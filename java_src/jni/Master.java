package jni;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

public class Master {
	
	private Vector<Competitor> competitors = new Vector<>();
	private HashSet<Integer> ids = new HashSet<>();
	private HashMap<Integer, Player> players = new HashMap<>();
	private HashMap<Pair2, Games> games = new HashMap<>();
	private HashMap<String, Country> countries = new HashMap<>();
	private HashMap<String, Sport> sports = new HashMap<>();
	
	private static Master instance = new Master();
	private Master() {}
	public static Master getInstance() {
		return instance;
	}
	
	public void loadEventsAthletes() throws FileNotFoundException {
		String eFname = "events.txt", aFname = "athletes.txt";
		
		BufferedReader readerE = new BufferedReader(new FileReader(eFname));
		Stream<String> streamE = readerE.lines();
		
		streamE.forEach(line -> {
			
			Pattern pE = Pattern.compile("([^ ]*) ([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)");
			Matcher mE = pE.matcher(line);
			if (mE.matches()) {
				String year = mE.group(1);
				String period = mE.group(2);
				String city = mE.group(3);
				String sport = mE.group(4);
				String discipline= mE.group(5);
				String type = mE.group(6);
				String country = mE.group(7);
				String tmp = mE.group(8);
				String medal = mE.group(9);
				
				Vector<Integer> playerIds = new Vector<>();
				if (type == "Team") {
					Pattern pT = Pattern.compile("([0-9]+)");
					Matcher mT = pT.matcher(tmp);
					while (mT.find()) {
						playerIds.add(Integer.parseInt(mT.group(1)));
						ids.add(Integer.parseInt(mT.group(1)));
					}					
				}
				
				Pair2 keyg = new Pair2(Integer.parseInt(year), period);
				games.putIfAbsent(keyg, new Games(Integer.parseInt(year), period, city));
				
				String keys = sport;
				sports.putIfAbsent(keys, new Sport(sport));
				
				String keyc = country;
				countries.putIfAbsent(keyc, new Country(country));
				
				Competitor c;
				if(type == "Individual") {
					c = new Athlete(games.get(keyg), countries.get(keyc), sports.get(keys), discipline, type, medal, playerIds.get(0));
				}
				else {
					c = new Team(games.get(keyg), countries.get(keyc), sports.get(keys), discipline, type, medal, playerIds);
				}
				
				competitors.add(c);
				games.get(keyg).getCompetitors().add(c);
				countries.get(keyc).getCompetitors().add(c);
				sports.get(keys).getCompetitors().add(c);
				
			} else System.out.println("Bad format in line " + line);
		});
		
		BufferedReader readerA = new BufferedReader(new FileReader(aFname));
		Stream<String> streamA = readerA.lines();
		
		streamA.forEach(line -> {
			Pattern pA = Pattern.compile("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)");
			Matcher mA = pA.matcher(line);	
			if (mA.matches()) {
				int id = Integer.parseInt(mA.group(1));
				String name = mA.group(2);
				String gender = mA.group(3);
				int years = mA.group(4).equals("NA") ? 0 : Integer.parseInt(mA.group(4));
				double height = mA.group(5).equals("NA") ? 0 : Double.parseDouble(mA.group(5));
				double weight = mA.group(6).equals("NA") ? 0 : Double.parseDouble(mA.group(6));
				
				if (ids.contains(id)) {
					players.putIfAbsent(id, new Player(id, name, gender, years, height, weight));
				}	
			}
		});
	}
	
	public static native int parseFiles(int year);
	
	public static native void filter(String sport, int year, String type, String medal);
	
	public static native String[] getPieData();
	
	public static native String[] getDisciplinesSummerData(int from, int to);
	
	public static native String[] getDisciplinesWinterData(int from, int to);
	
	public static native String[] getHieghtSummerData(int from, int to);
	
	public static native String[] getHeightWinterData(int from, int to);
	
	public static native String[] getWeightSummerData(int from, int to);
	
	public static native String[] getWeightWinterData(int from, int to);
	
	public static void loadData(int year) {
		parseFiles(year);
	}
	
	public static void main(String[] args) {
		
		System.loadLibrary("masterDLL");
		
		try {
			getInstance().loadEventsAthletes();
		} catch (FileNotFoundException e) {
			System.out.println("Bad file path");
		}
				
		Olimpics o = new Olimpics();
				
	}
	
}
