class Tester
  def initialize
    @tests = {
      :nat_simple => {
        :name => "not a triangle test :: simple",
        :output => "not a triangle\n"
      },
      :nat_hard => {
        :name => "not a triangle test :: hard", 
        :output => "not a triangle\n"
      },
      :iso_acute => {
        :name => "isosceles test :: acute",
        :output => "isosceles acute\n"
      },
      :iso_obtuse => {
        :name => "isosceles test :: obtuse",
        :output => "isosceles obtuse\n"
      },
      :iso_right => {
        :name => "isosceles test :: right",
        :output => "isosceles right\n"
      },
      :sca_acute => {
        :name => "scalene test :: acute",
        :output => "scalene acute\n"
      },
      :sca_obtuse => {
        :name => "scalene test :: obtuse",
        :output => "scalene obtuse\n"
      },
      :sca_right => {
        :name => "scalene test :: right",
        :output => "scalene right\n"
      }
    }

    @tests_ran = 0
    @tests_failed = 0
    @tests_passed = 0
  end

  def run_test (input, sym)
    @tests_ran += 1

    output = `#{input}`

    if output != @tests[sym][:output]
      return fails(sym, output) 
    end

    return passes sym
  end

  def summary
    puts ""
    puts "Ran #{@tests_ran} tests, #{@tests_failed} failed, #{@tests_passed}"\
          " passed."
    puts ""
  end

  private

  def fails test_sym, output
    @tests_failed += 1

    output.gsub!("\n","")
    expected = @tests[test_sym][:output].gsub("\n", "")

    puts "Failed #{@tests[test_sym][:name]}.  "
    puts "\tExpected '#{expected}' but got '#{output}' instead"
  end

  def passes test_sym
    @tests_passed += 1

    puts "Passed #{@tests[test_sym][:name]}!"
  end
end

test_harness = Tester.new
test_harness.run_test("./triangle 0 0 0 0 0 0", :nat_simple)
test_harness.run_test("./triangle 1 1 2 2 3 3", :nat_hard)
test_harness.run_test("./triangle 1 1 2 4 3 1", :iso_acute)
test_harness.run_test("./triangle 1 1 3 2 4 1", :iso_obtuse)
test_harness.run_test("./triangle 1 1 1 2 2 1", :iso_right)
test_harness.run_test("./triangle 1 1 5 1 5 4", :sca_right)
test_harness.run_test("./triangle 1 1 4 2 6 1", :sca_obtuse)
test_harness.run_test("./triangle 1 1 2 2 4 1", :sca_acute)
test_harness.summary