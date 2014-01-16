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
    "Ran #{@tests_ran} tests, #{@tests_failed} failed, #{@tests_passed} passed."
  end

  def reset
    @tests_ran = 0
    @tests_failed = 0
    @tests_passed = 0
  end

  private

  def fails test_sym, output
    @tests_failed += 1
  end

  def passes test_sym
    @tests_passed += 1
  end
end

