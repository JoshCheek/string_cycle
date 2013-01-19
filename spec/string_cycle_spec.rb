require 'spec_helper'

describe StringCycle do
  let(:size)            { 2 }
  let(:part1)           { "AB" }
  let(:part2)           { "CD" }
  let(:part3)           { "EF" }
  let(:original_string) { part1 + part2 + part3 }
  let(:cycler)          { described_class.new original_string }

  # delete this after its properly implemented, this just shows some stuff works
  specify '#to_s returns the string in its current form' do
    cycler.to_s.should == original_string
  end

  specify '#peek will show the next string without mutation' do
    cycler.peek(size).should == part1
    cycler.to_s.should == original_string
  end

  specify '#cycle will rotate through the string infinitely' do
    cycler.cycle.should == part1
    cycler.to_s.should == part2 + part3 + part1

    cycler.cycle.should == part2
    cycler.to_s.should == part3 + part1 + part2

    cycler.cycle.should == part3
    cycler.to_s.should == original_string

    cycler.cycle.should == part1
    cycler.to_s.should == part2 + part3 + part1
  end
end
