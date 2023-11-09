package jni;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Canvas;
import java.awt.CardLayout;
import java.awt.Checkbox;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Olimpics extends Frame {

	private TextField sportTextField = new TextField();
	private Label sportLabel = new Label("Sport");
	private TextField yearTextField = new TextField();
	private Label yearLabel = new Label("Year");
	private TextField typeTextField = new TextField();
	private Label typeLabel = new Label("Type(Individual/Team)");
	private TextField medalTextField = new TextField();
	private Label medalLabel = new Label("Medal(Gold/Silver/Bronze)");
	
	private TextField fromTextField = new TextField();
	private Label fromLabel = new Label("Year from");
	private TextField toTextField = new TextField();
	private Label toLabel = new Label("Year to");
	
	private Panel loadPanel = new Panel();
	private Label loadLabel = new Label("Year to load(0 for all)");
	private TextField loadingYearTextField = new TextField();
	private Button loadButton = new Button("Load");
	
	private Button participantsButton = new Button("Participants");
	private Button disciplinesButton = new Button("Disciplines");
	private Button heightButton = new Button("Height");
	private Button weightButton = new Button("Weight");
	
	private Pie pie = new Pie();
	
	private XY xy = new XY();
		
	public Olimpics() {
		setBounds(0, 0, 1920, 1080);
		setTitle("Olympics");
		setResizable(false);
		
		addWindowListener(new WindowAdapter() {
		
			@Override
			public void windowClosing(WindowEvent e) {
				dispose();
			}
			
		});
		
		participantsButton.addActionListener((ae) -> {
			xy.setVisible(false);
			pie.setVisible(true);
			
			Master.filter(sportTextField.getText(),
							Integer.parseInt(!(yearTextField.getText().equals("")) ? yearTextField.getText() : "0"),
							typeTextField.getText(),
							medalTextField.getText());	
			System.out.println("----------------------");
			for(String s : Master.getPieData()) {
				System.out.println(s);
			}
			
			pie.update(Master.getPieData());
		});
		
		disciplinesButton.addActionListener((ae) -> {
			pie.setVisible(false);
			xy.setVisible(true);
			
			int from = Integer.parseInt(!(fromTextField.getText().equals("")) ? fromTextField.getText() : "1896");
			int to = Integer.parseInt(!(toTextField.getText().equals("")) ? toTextField.getText() : "2016");
			System.out.println("-----Summer-----");
			for(String s : Master.getDisciplinesSummerData(from, to)) {
					System.out.println(s);
			}
			System.out.println("-----Winter-----");
			for(String s : Master.getDisciplinesWinterData(from, to)) {
				System.out.println(s);
			}
			xy.update(Master.getDisciplinesSummerData(from, to),
					Master.getDisciplinesWinterData(from, to),
					from, to);
			
		});
		
		heightButton.addActionListener((ae) -> {
			pie.setVisible(false);
			xy.setVisible(true);
			
			int from = Integer.parseInt(!(fromTextField.getText().equals("")) ? fromTextField.getText() : "1896");
			int to = Integer.parseInt(!(toTextField.getText().equals("")) ? toTextField.getText() : "2016");
			System.out.println("-----Summer-----");
			for(String s : Master.getHieghtSummerData(from, to)) {
					System.out.println(s);
			}
			System.out.println("-----Winter-----");
			for(String s : Master.getHeightWinterData(from, to)) {
				System.out.println(s);
			}
			xy.update(Master.getHieghtSummerData(from, to),
					Master.getHeightWinterData(from, to),
					from, to);
			
		});
		
		weightButton.addActionListener((ae) -> {
			pie.setVisible(false);
			xy.setVisible(true);
			
			int from = Integer.parseInt(!(fromTextField.getText().equals("")) ? fromTextField.getText() : "1896");
			int to = Integer.parseInt(!(toTextField.getText().equals("")) ? toTextField.getText() : "2016");
			System.out.println("-----Summer-----");
			for(String s : Master.getWeightSummerData(from, to)) {
					System.out.println(s);
			}
			System.out.println("-----Winter-----");
			for(String s : Master.getWeightWinterData(from, to)) {
				System.out.println(s);
			}
			xy.update(Master.getWeightSummerData(from, to),
					Master.getWeightWinterData(from, to),
					from, to);
			
		});
		
		loadButton.addActionListener((ae) -> {
			loadButton.setEnabled(false);
			Master.loadData(Integer.parseInt(!(loadingYearTextField.getText().equals("")) ? loadingYearTextField.getText() : "0"));
			
			participantsButton.setEnabled(true);
			disciplinesButton.setEnabled(true);
			heightButton.setEnabled(true);
			weightButton.setEnabled(true);
			
			loadPanel.setVisible(false);
			pie.setVisible(true);
		});
		
		populateWindow();
		
		setVisible(true);
	}
	
	private void populateWindow() {
		Panel topPanel = new Panel();
		topPanel.setBackground(Color.CYAN);
		topPanel.setLayout(new FlowLayout());
		
		topPanel.add(sportLabel);
		sportTextField.setPreferredSize(new Dimension(100, 20));
		topPanel.add(sportTextField);
		
		topPanel.add(yearLabel);
		yearTextField.setPreferredSize(new Dimension(100, 20));
		topPanel.add(yearTextField);
		
		topPanel.add(typeLabel);
		typeTextField.setPreferredSize(new Dimension(100, 20));
		topPanel.add(typeTextField);
		
		topPanel.add(medalLabel);
		medalTextField.setPreferredSize(new Dimension(100, 20));
		topPanel.add(medalTextField);
				
		participantsButton.setEnabled(false);
		topPanel.add(participantsButton);
		
		add(topPanel, BorderLayout.NORTH);
		
		Panel bottomPanel = new Panel();
		bottomPanel.setLayout(new FlowLayout());
		
		bottomPanel.add(fromLabel);
		fromTextField.setPreferredSize(new Dimension(100, 20));
		bottomPanel.add(fromTextField);
		
		bottomPanel.add(toLabel);
		toTextField.setPreferredSize(new Dimension(100, 20));
		bottomPanel.add(toTextField);
		
		disciplinesButton.setEnabled(false);
		bottomPanel.add(disciplinesButton);
		heightButton.setEnabled(false);
		bottomPanel.add(heightButton);
		weightButton.setEnabled(false);
		bottomPanel.add(weightButton);
		
		add(bottomPanel, BorderLayout.SOUTH);
		
		Panel graphsPanel = new Panel();
		graphsPanel.setLayout(new CardLayout());
		
		graphsPanel.add(pie);
		
		graphsPanel.add(xy);
		
		loadPanel.add(loadLabel);
		loadingYearTextField.setPreferredSize(new Dimension(100, 20));
		loadPanel.add(loadingYearTextField);
		loadPanel.add(loadButton);
		graphsPanel.add(loadPanel);
		loadPanel.setVisible(true);
		
		add(graphsPanel, BorderLayout.CENTER);
		
		pack();
	}
	
}
