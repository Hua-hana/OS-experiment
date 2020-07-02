
import java.util.concurrent.*;
import java.util.Arrays;
import java.util.List;
import java.io.*;
public class quicksort extends RecursiveAction
{
    static final int MAX_SIZE = 10000;
    static final int THRESHOLD = 100;
    static final int MAX_NUM = 100000;

    private int begin;
    private int end;
    private int[] array;


    public quicksort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;

    }

    protected void compute() {
        if (end - begin < THRESHOLD) {
            // conquer stage 
            for(int lh=begin;lh<=end-1;++lh)
		        for(int rh=lh+1;rh<=end;++rh)
			        if(array[rh]<array[lh])
			            {int tmp=array[lh];array[lh]=array[rh];array[rh]=tmp;}
	return;
        }
        else {
            // divide stage 
            int tmp=array[begin];
            int low=begin,high=end;
            while(low<=high){
                while(low<=high&&array[high]>tmp)--high;
                if(low<=high){array[low]=array[high];low++;}
                while(low<=high&&array[low]<=tmp)++low;
                if(low<=high){array[high]=array[low];high--;}
            }
            array[low]=tmp;
           
	invokeAll(new quicksort(begin, low-1, array),new quicksort(low + 1, end, array));
        }
    }

	public static void main(String[] args) {
		ForkJoinPool pool = new ForkJoinPool();
        	int nowsize;
		
		// create SIZE random integers between 0 and 9
		java.util.Random rand = new java.util.Random();
        nowsize=rand.nextInt(MAX_SIZE);
        int []array = new int[nowsize];
	 
		for (int i = 0; i < nowsize; i++) {
			array[i] = rand.nextInt(MAX_NUM);
		}		
		
        //write to qsort1.txt
         try { 
            File writename = new File("qsort1.txt"); // 相对路径，如果没有则要建立一个新的output。txt文件  
            writename.createNewFile();
		    StringBuilder sb = new StringBuilder();
		    for(int i = 0; i < nowsize; i++){
		            sb.append(array[i]).append("\n");
		    }
		    sb.deleteCharAt(sb.length() -1);
                BufferedWriter out = new BufferedWriter(new FileWriter(writename));  
                out.write(sb.toString());//  
                out.flush(); // 把缓存区内容压入文件  
                out.close(); // 最后记得关闭文件  
      
            } catch (Exception e) {  
                e.printStackTrace();  
            }  




		quicksort task = new quicksort(0, nowsize-1, array);

		pool.invoke(task);

        //write the result
        try { 
            File writename = new File("qsort2.txt"); 
            writename.createNewFile();
		    StringBuilder sb = new StringBuilder();
		    for(int i = 0; i < nowsize; i++){
		            sb.append(array[i]).append("\n");
		    }
		    sb.deleteCharAt(sb.length() -1);
                BufferedWriter out = new BufferedWriter(new FileWriter(writename));  
                out.write(sb.toString());//  
                out.flush(); // 把缓存区内容压入文件  
                out.close(); // 最后记得关闭文件  
      
            } catch (Exception e) {  
                e.printStackTrace();  
            }  



		System.out.println("Quicksort\nNumber: "+nowsize);
	}
}


