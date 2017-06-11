require 'Benchmark'

AdjList = Struct.new(:pr, :out, :aList)

class BasicGraph
  def initialize
    @hash = Hash.new
  end

  def add_edge(src, dest)
    unless @hash.key?(src)
      @hash[src] = AdjList.new(0.0, 0, Array.new)
    end
    @hash[src].out += 1
    unless @hash.key?(dest)
      @hash[dest] = AdjList.new(0.0, 0, Array.new)
    end
    @hash[dest].aList.push(src)
  end

  def calculate_page_rank(iterations, x)
    d = Float(0.85)
    n = Float(@hash.size)
    restartRate = Float((1.0 - d) / n)
    sinkNodes = Array.new
    newPageRank = Hash.new
    @hash.each do |key, node|
      node.pr = 1.0 / n
      sinkNodes.push key unless node.out > 0
    end
    Integer(iterations).times do |i|
      x.report("Iter #{i+1}\t"){
        sinkNodesRank = Float(0.0)
        sinkNodes.each do |sinkNode|
          sinkNodesRank += @hash[sinkNode].pr
        end
        @hash.each do |key, node|
          newPageRank[key] = restartRate
          newPageRank[key] += (d * sinkNodesRank) / n
          node.aList.each do |inNode|
            newPageRank[key] += ((d * @hash[inNode].pr) / @hash[inNode].out)
          end
        end
        @hash.each do |key, node|
          node.pr = newPageRank[key]
        end
      }
    end
  end

  def print_graph
    @hash.each do |key, node|
      puts "Inverted AdjList for Vertex #{key}"
      puts "Out: #{node.out}"
      node.aList.each do |inNode|
        print "<- #{inNode} "
      end
      puts
    end
  end

  def print_scores
    puts "\nScores:"
    sum = 0
    @hash.each do |key, node|
      puts "#{key}\t#{node.pr}"
      sum += node.pr
    end
    puts "Sum: #{sum}"
  end
end

if __FILE__ == $0
  graph = BasicGraph.new
  Benchmark.bm do |x|
    x.report("Memory\t") {
      File.open('/Users/omar/Documents/Tsinghua/Spring 2016/CPP/PageRank/linkgraph.txt').each do |line|
        graph.add_edge(line[/([0-9]+)/], line[/([0-9]+)\n/][0..-2])
      end
    }
    graph.calculate_page_rank(15, x)
  end
  # graph.print_scores
end