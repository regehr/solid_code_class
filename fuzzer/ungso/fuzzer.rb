# File:  tc_simple_number.rb
 
require "test/unit"
 
class TestPrintf < Test::Unit::TestCase


  def setup    
    system('/usr/local/musl/bin/musl-gcc hello.c -o m') 
    system('gcc hello.c -o g')

  end

  def test_simple

    s = "hello\n"
    stdout = IO.popen('./m -s '+s)
    assert_equal(s, stdout.readlines[0])
    
  end
 
  def test_gcc

    s = "hello\n"
    stdout1 = IO.popen('./m -s '+s)
    stdout2 = IO.popen('./g -s '+s)
    assert_equal(stdout1.readlines[0], stdout2.readlines[0])
    
  end

  def test_int

    exp = 31
    beg = (-1) * (2**exp)
    last = (2**exp) - 1
    (beg..last).step(2**21) do |beg|
      stdout1 = IO.popen('./m -i ' +beg.to_s)
      stdout2 = IO.popen('./g -i '+beg.to_s)
      assert_equal(stdout1.readlines[0], stdout2.readlines[0])
      end
  end



end
