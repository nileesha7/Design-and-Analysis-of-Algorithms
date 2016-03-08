import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Dijkstra {

	int N;
	int sourceNode;
	int minNode;
	int currentNode;
	int newCost;
	int[][] costMatrix;
	int[] fatherArray;
	int[] markedArray;
	int[] bestCostArray;

	public Dijkstra(int numOfNodes, int sourceNode) {
		N = numOfNodes;
		this.sourceNode = sourceNode - 1;

		minNode = this.sourceNode;
		currentNode = 0;
		newCost = 0;

		costMatrix = new int[N][N];
		// initialize cost Matrix Array

		for (int i = 0; i < costMatrix.length; i++) {
			for (int j = 0; j < costMatrix[i].length; j++) {
				if (i == j) {
					costMatrix[i][j] = 0;
				} else
					costMatrix[i][j] = 9999;
			}
		}

		// initialize father Array
		fatherArray = new int[N];
		for (int i = 0; i < fatherArray.length; i++) {
			fatherArray[i] = i;
		}

		markedArray = new int[N];
		for (int i = 0; i < markedArray.length; i++) {
			markedArray[i] = 0;
		}

		// initialize best Cost Array
		bestCostArray = new int[N];
		for (int i = 0; i < bestCostArray.length; i++) {
			bestCostArray[i] = 9999;
		}

		bestCostArray[this.sourceNode] = 0;
	}

	public int computeCost(int minNode, int currentNode) {
		return bestCostArray[minNode] + costMatrix[minNode][currentNode];
	}

	public void updateMarkedArray(int index) {
		markedArray[index] = 1;
	}

	public void updateFatherArray(int currentNode, int minNode) {
		fatherArray[currentNode] = minNode;
	}

	public void updateBestCostArray(int currentNode, int newCost) {
		bestCostArray[currentNode] = newCost;
	}

	public void debugPrint(FileWriter out2) {
		try {
			System.out.println();
			out2.write("\n" + "\n");
			System.out.println("Source Node: " + (sourceNode + 1) + "\n");
			out2.write("Source Node: " + (sourceNode + 1) + "\n");
			System.out.println("Father Array: ");
			out2.write("Father Array: ");
			for (int i : fatherArray) {
				System.out.print((i + 1) + ", ");
				out2.write((i + 1) + ", ");
			}
			System.out.println();
			out2.write("\n");
			System.out.println("Best Cost Array");

			out2.write("Best Cost Array: ");
			for (int i : bestCostArray) {
				System.out.print(i+", ");
				out2.write(i + ", ");
			}

			out2.write("\n");
			System.out.println();

			out2.write("Marked Array:");
			System.out.print("Marked Array: ");

			for (int i : markedArray) {
				System.out.print(i+", ");

				out2.write(i + ", ");
			}

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	public void debugPrint_costMatrix(int[][] costMatrix, FileWriter out2) {
		try {
			out2.write("The cost matrix: " + "\n");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		for (int i = 0; i < costMatrix.length; i++) {
			for (int j = 0; j < costMatrix[i].length; j++) {
				try {
					out2.write(costMatrix[i][j] + " ");
				} catch (IOException e) {
					e.printStackTrace();
				}
				System.out.print(costMatrix[i][j] + " ");
			}
			try {
				out2.write("\n");
			} catch (IOException e) {
				e.printStackTrace();
			}

			System.out.println();
		}
	}

	private void findNPrintShortestPath(int n, FileWriter out1) {
		String strPath;
		int father=findFather(n);
		strPath = "<>"+(n+1);
		
		if(n==fatherArray[n] && n!=sourceNode){
			try {
				System.out.println("No path from "+(sourceNode +1) +" to"+(n+1)+"\n");
				out1.write("No path from "+(sourceNode +1) +" to "+(n+1)+"\n");
				return;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		while(father!=sourceNode){
			strPath="<>"+(father+1)+strPath;
			father=findFather(father);
		}
		strPath=(sourceNode+1)+strPath +": Cost ="+bestCostArray[n];
		System.out.println(strPath);
		try {
			out1.write(strPath+"\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private int findFather(int n) {
		return fatherArray[n];
	}

	public void dijkstra_SSS(Scanner input, FileWriter out1, FileWriter out2) {
		boolean allNodesMarked = false;
		
		// populate costMatrix
		while (input.hasNext()) {
			int Ni = input.nextInt() - 1;
			int Nj = input.nextInt() - 1;
			int cost = input.nextInt();
			costMatrix[Ni][Nj] = cost;
		}

		debugPrint_costMatrix(costMatrix, out2);
		debugPrint(out2);

		for(int n=0; n<N; n++){
			// Find unmarked node with smallest cost
			int minCost = 9999;
			for (int i = 0; i < bestCostArray.length; i++) {
				if (markedArray[i] == 0) {
					if (bestCostArray[i] < minCost) {
						minCost = bestCostArray[i];
						minNode = i;
					}
				}
			}
			System.out.println("min node: " + minNode);
			try {
				out2.write("\n" + "\n" + "Min Node: " + (minNode + 1));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			markedArray[minNode] = 1;

			// Expanding min Node

			// Find the next unmarked node

			for (int i = 0; i < markedArray.length; i++) {
				if (markedArray[i] == 0) {
					currentNode = i;
					newCost = computeCost(minNode, currentNode);
				}
				if (newCost < bestCostArray[i]) {
					updateBestCostArray(currentNode, newCost);
					updateFatherArray(currentNode, minNode);
				}

			}
			debugPrint(out2);
			

		}
		try {
			out1.write("Let the source Node be "+ (sourceNode+1) +". There are "+N+" nodes in the graph G."+"\n"+"\n");
			System.out.println("Let the source Node be "+ (sourceNode+1) +". There are "+N+" nodes in the graph G."+"\n"+"\n");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		for(int k=0; k<N; k++){
			findNPrintShortestPath(k, out1);
		}
		
	}
}
