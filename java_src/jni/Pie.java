package jni;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

public class Pie extends Canvas {

	private Random r = new Random();
	private Color c;
	private ArrayList<Pair> chunks = new ArrayList<>();
	
	public Pie(){
		setBackground(Color.LIGHT_GRAY);
		setSize(490, 490);
		setVisible(false);
	}
	
	public void update(String[] data) {
		chunks.clear();
		for(int i = 0; i < data.length ; i += 2) chunks.add(new Pair(data[i], Integer.parseInt(data[i + 1])));
		chunks.sort((p1, p2) -> (p2.getSecond() - p1.getSecond()));
		for(Pair p : chunks) {
			System.out.println(p);
		}
		repaint();
	}
	
	@Override
	public void paint(Graphics g) {
		if(chunks.isEmpty()) return;
		int sum = 0;
		int diametar = 200;
		for(Pair p : chunks) {
			sum += p.getSecond();
		}
		int angle = 0;
		g.translate(getWidth() / 2, getHeight() / 2);
		int bound = chunks.size() >= 10 ? 10 : chunks.size();
		for(int i = 0; i < bound; i++) {
			if(i < 9) {
				c = new Color(r.nextFloat(), r.nextFloat(), r.nextFloat());
				g.setColor(c);
				g.fillArc(-150, -150, 300, 300, angle, chunks.get(i).getSecond() * 360 / sum);
				g.drawString(chunks.get(i).getFirst(),
						(int)(diametar * Math.cos((angle + chunks.get(i).getSecond() * 360 / sum / 2) * Math.PI / 180)),
						(int)(-diametar * Math.sin((angle + chunks.get(i).getSecond() * 360 / sum / 2) * Math.PI / 180)));
				angle += chunks.get(i).getSecond() * 360 / sum;
			}
			else {
				c = new Color(r.nextFloat(), r.nextFloat(), r.nextFloat());
				g.setColor(c);
				g.fillArc(-150, -150, 300, 300, angle, 360 - angle);
				g.drawString("Others",
						(int)(diametar * Math.cos((angle + (360 - angle) / 2) * Math.PI / 180)),
						(int)(-diametar * Math.sin((angle + (360 - angle) / 2) * Math.PI / 180)));
			}
		}
		g.fillArc(-150, -150, 300, 300, angle, 360 - angle); //ako je angle manji od 360 na kraju zbog celobrojnog deljenja
	}
}
