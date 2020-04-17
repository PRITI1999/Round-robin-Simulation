import java.util.*;

class SchedulingImp{
	public static void main(String args[]){
		SchedulingImp obj = new SchedulingImp();
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] arrivalTime = new int[n];
		int[] arrivalTimeTemp = new int[n];
		int[] burstTime = new int[n];
		int sum=0;
		for(int i = 0; i < n; i++){
			arrivalTime[i] = sc.nextInt();
			burstTime[i] = sc.nextInt();
			sum+= burstTime[i];
		}
		int q = sc.nextInt();
		obj.copyArrivalTime(arrivalTimeTemp, arrivalTime);
		obj.roundRobin(n, arrivalTimeTemp, burstTime, sum, q);
	}
	void copyArrivalTime(int d[], int s[]){
		for(int i = 0; i < s.length; i++){
			d[i] = s[i];
		}
	}
	int max(int n, int a[]){
		int maxVal = Integer.MIN_VALUE;
		for(int i = 0; i < n; i++){
			if(a[i]>maxVal){
				maxVal = a[i];
			}
		}
		return maxVal;
	}
	void roundRobin(int n, int[] arrivalTime, int[] burstTime, int sum, int q){
		int k = 0;
		int i = 0;
		String gantt = "0";
		String ready = "";
		Queue<Integer> readyQueue = new LinkedList<Integer>(); 
		addToQueue(n, arrivalTime, 0, readyQueue);
		readyQueue.add(10000);
		int maxArrival = max(n, arrivalTime);
		while(k!=sum){
			if(readyQueue.isEmpty())
				continue;
			int current = readyQueue.remove();
			while(current == 10000){
				ready += "| ";
				current = readyQueue.remove();
			}
			ready += current+" ";
			if(burstTime[current]>q){
				gantt += " P"+current+" "+(k+q);
				k = k+q;
				burstTime[current]-=q;
				addToQueue(n, arrivalTime, k, readyQueue);
				readyQueue.add(current);
			}
			else{
				gantt += " P"+current+" "+(k+burstTime[current]);
				k=k+burstTime[current];
				addToQueue(n, arrivalTime, k, readyQueue);
				burstTime[current]=0;
			}
			readyQueue.add(10000);
		}	
		System.out.println(ready);
		System.out.println(gantt);
	}
	void addToQueue(int n, int a[], int k, Queue<Integer> readyQueue){
		int minVal = Integer.MAX_VALUE;
		int minPos = Integer.MAX_VALUE;
		while(minPos != -1){
			minVal = Integer.MAX_VALUE;
			minPos = -1;
			for(int i = 0; i < n; i++){
				if(a[i] <= k && a[i] < minVal){
					minVal = a[i];
					minPos = i;
				}
			}
			if(minPos != -1){
				a[minPos] = Integer.MAX_VALUE;
				//System.out.println(minPos);
				readyQueue.add(minPos);
			}
		}
	}
}
