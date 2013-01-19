# -*- encoding: utf-8 -*-
# $:.push File.expand_path("../lib", __FILE__)

Gem::Specification.new do |s|
  s.name        = "string_cycle"
  s.version     = '0.0.0'
  s.authors     = ["Josh Cheek"]
  s.email       = ["josh.cheek@gmail.com"]
  s.homepage    = "TBD"
  s.summary     = %q{TBD}
  s.description = %q{TBD}

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]

  s.add_development_dependency "rake"
  s.add_development_dependency "rspec", "~> 2.4"
  s.add_development_dependency "rake-compiler"
end
