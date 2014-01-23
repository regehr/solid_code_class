require File.join(File.dirname(__FILE__), 'tester')

class ClassTester
  def initialize
    @test_harness = Tester.new
  end

  def run
    Dir.foreach("../") do |f|
      # ignore a couple unnecessary directories
      next if (f == "." || f == "..")
      next if File.file?("../" + f)

      Dir.chdir("../" + f)

      begin
        run_tests
        summary f
      rescue
        next
      end
      @test_harness.reset
    end

    puts "Finished generating file"
  end

  private

  ### ---
  ### Runs the tests against the current user (runs make, then runs make clean)
  ### +++
  def run_tests
    `make > dev/null`
    @test_harness.run_test("./triangle 0 0 0 0 0 0", :nat_simple)
    @test_harness.run_test("./triangle 1 1 2 2 3 3", :nat_hard)
    @test_harness.run_test("./triangle 1 1 3 2 1 3", :iso_acute)
    @test_harness.run_test("./triangle 1 1 3 2 5 1", :iso_obtuse)
    @test_harness.run_test("./triangle 1 1 0 2 0 1", :iso_right)
    @test_harness.run_test("./triangle 1 1 5 1 5 4", :sca_right)
    @test_harness.run_test("./triangle 1 1 4 2 6 1", :sca_obtuse)
    @test_harness.run_test("./triangle 1 1 2 2 4 1", :sca_obtuse)
    @test_harness.run_test("./triangle 0 0 1 3 4 0", :sca_acute)
    `make clean`
  end

  def summary dirname
    File.open("../jmcdonald-ut/test-results.txt", 'a') do |file|
      file.write(dirname)
      file.write(" ")
      file.write(@test_harness.summary)
      file.write("\n")
    end
  end
end

class_tester = ClassTester.new
class_tester.run