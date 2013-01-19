require 'rake/extensiontask'

Rake::ExtensionTask.new(
  'string_cycle',
  Gem::Specification.load('string_cycle.gemspec')
)

desc 'Open a console with the lib loaded'
task console: :compile do
  lib_path = File.expand_path '../lib', __FILE__
  sh 'bundle', 'exec', 'pry',
          '-I', lib_path,
          '-r', 'string_cycle'
end
