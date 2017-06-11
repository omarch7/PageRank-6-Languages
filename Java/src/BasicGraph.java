import java.io.*;
import java.util.HashMap;
import java.util.Vector;

/**
 * Created by omar on 14/4/16.
 */
public class BasicGraph{
    public static void main(String args[]){
        BasicGraph graph = new BasicGraph();

        float start = System.nanoTime();
        File file = new File("/Users/omar/Documents/Tsinghua/Spring 2016/CPP/PageRank/linkgraph.txt");
        try{
            FileInputStream fis = new FileInputStream(file);
            BufferedReader br = new BufferedReader(new InputStreamReader(fis));
            String line;
            while((line = br.readLine()) != null){
                final String[] values = line.split("\t");
                graph.addEdge(values[0], values[1]);
            }
            fis.close();
            float end = System.nanoTime();
            System.out.println("Loaded into memory in " + (end - start) / 1000000 + "ms");
            graph.calculatePageRank(15);
//        graph.printScores();
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public HashMap<String, AdjListNode> map = new HashMap<>();

    public void addEdge(String src, String dest){
        if(!map.containsKey(src)){
            map.put(src, new AdjListNode());
        }
        map.get(src).out++;
        if(!map.containsKey(dest)){
            map.put(dest, new AdjListNode());
        }
        map.get(dest).list.add(src);
    }

    public void calculatePageRank(int iterations){
        float d = 0.85f;
        float n = Float.valueOf(map.size());
        float restartRate = (1.0f - d) / n;
        HashMap<String, Float> newPageRank = new HashMap<>();
        Vector<String> sinkNodes = new Vector<>();
        for(String node : map.keySet()){
            map.get(node).pr = 1.0f / n;
            if(map.get(node).out==0){
                sinkNodes.add(node);
            }
        }
        int num = iterations;
        while(iterations>0){
            double startTime = System.nanoTime();
            float sinkNodesRank = 0.0f;
            for(String sinkNode : sinkNodes){
                sinkNodesRank += map.get(sinkNode).pr;
            }
            for(String node : map.keySet()){
                float npg = restartRate;
                npg += (d * sinkNodesRank) / n;
                for(String inNode : map.get(node).list){
                    npg += ((d * map.get(inNode).pr) / map.get(inNode).out);
                }
                newPageRank.put(node, npg);
            }
            for(String node : map.keySet()){
                map.get(node).pr = newPageRank.get(node);
            }
            iterations--;
            double endTime   = System.nanoTime();
            System.out.println("Iteration " + (num - iterations) + " completed in " + (endTime-startTime) / 1000000 + "ms");
        }
    }

    public void printScores(){
        float sum = 0.0f;
        System.out.println("Scores:");
        for(String node : map.keySet()){
            System.out.println(node + "\t" + map.get(node).pr);
            sum += map.get(node).pr;
        }
        System.out.println("Sum: " + sum);
    }

    public void printGraph(){
        for(String node : map.keySet()){
            System.out.println("Inverted AdjList for Vertex " + node);
            for(String inNode : map.get(node).list){
                System.out.print("<- " + inNode + " ");
            }
            System.out.println();
        }
    }
}

class AdjListNode{
    public int out = 0;
    public float pr = 0;
    public Vector<String> list = new Vector<>();
}