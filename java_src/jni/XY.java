package jni;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

public class XY extends Canvas {
	
	private ArrayList<Pair> summer = new ArrayList<>();
	private ArrayList<Pair> winter = new ArrayList<>();
	private int gwidth = 400;
	private int gheight = 300;
	private double minVal = 1000000;
	private double maxVal = 0;
	private boolean initialized = false;
	private int from = 1900;
	private int to = 2000;
	
	
	public XY() {
		setBackground(Color.GRAY);
		setSize(490,  490);
		setVisible(false);
	}
	
	public void update(String[] summerData, String[] winterData, int from, int to) {
		summer.clear();
		winter.clear();
		minVal = 1000000;
		maxVal = 0;
		for(int i = 0; i < summerData.length ; i += 2) {
			summer.add(new Pair(summerData[i], Integer.parseInt(summerData[i + 1])));
			if(Integer.parseInt(summerData[i + 1]) > maxVal) maxVal = Integer.parseInt(summerData[i + 1]);
			if(Integer.parseInt(summerData[i + 1]) < minVal) minVal = Integer.parseInt(summerData[i + 1]);
		}
		summer.sort((p1, p2) -> (Integer.parseInt(p2.getFirst()) - Integer.parseInt(p1.getFirst())));
		for(int i = 0; i < winterData.length ; i += 2) {
			winter.add(new Pair(winterData[i], Integer.parseInt(winterData[i + 1])));
			if(Integer.parseInt(winterData[i + 1]) > maxVal) maxVal = Integer.parseInt(winterData[i + 1]);
			if(Integer.parseInt(winterData[i + 1]) < minVal) minVal = Integer.parseInt(winterData[i + 1]);
		}
		winter.sort((p1, p2) -> (Integer.parseInt(p2.getFirst()) - Integer.parseInt(p1.getFirst())));
		System.out.println("-----summer-----");
		for(Pair p : summer) {
			System.out.println(p);
		}
		System.out.println("-----winter-----");
		for(Pair p : winter) {
			System.out.println(p);
		}
		System.out.println("-----minVal maxVal-----");
		System.out.println(minVal);
		System.out.println(maxVal);
		this.from = from;
		this.to = to;
		initialized = true;
		repaint();
	}
	
	@Override
	public void paint(Graphics g) {
		g.drawRect((getWidth() - gwidth) / 2, (getHeight() - gheight) / 2, gwidth, gheight);
		g.translate((getWidth() - gwidth) / 2, (getHeight() - gheight) / 2 + gheight);
		if(!initialized) return;
		drawTicks(g);
		drawPoints(g);
	}
	
	private void drawPoints(Graphics g) {
		for(Pair p : summer) {
			circle((int)(gwidth * (Integer.parseInt(p.getFirst()) - from) / (to - from)),
					-(int)(gheight * (p.getSecond() - minVal) / (maxVal - minVal)),
					g, Color.RED);
		}
		for(Pair p : winter) {
			circle((int)(gwidth * (Integer.parseInt(p.getFirst()) - from) / (to - from)),
					-(int)(gheight * (p.getSecond() - minVal) / (maxVal - minVal)),
					g, Color.BLUE);
		}
	}

	private void drawTicks(Graphics g) {
		int numOfTicks = 6;
		for(int i = 0; i < numOfTicks; i++) {
			g.drawString("" + (from + i * (to - from) / numOfTicks), i * gwidth / numOfTicks - 10  , 15);
			g.drawString("" + (int)(minVal + i * (maxVal - minVal) / numOfTicks), -25 , -i * gheight / numOfTicks);
		}
		g.drawString("" + to, gwidth - 10, 15);
		g.drawString("" + (int)maxVal, -25, -gheight);
	}

	public void circle(int x, int y, Graphics g, Color c) {
		g.setColor(c);
		g.fillOval(x - 5, y - 5, 10, 10);
	}
}
