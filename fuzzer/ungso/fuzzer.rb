# File:  tc_simple_number.rb
 
require "test/unit"
 
class TestPrintf < Test::Unit::TestCase

  def setup    
    system('/usr/local/musl/bin/musl-gcc hello.c')
  end

  def test_simple

    s = "hello\n"
    stdout = IO.popen('./a.out '+s)
    assert_equal(s, stdout.readlines[0])
    
  end
 
end
