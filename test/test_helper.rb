#!/usr/bin/env ruby

# SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
#
# SPDX-License-Identifier: MIT

require 'socket'
require 'tmpdir'
require 'fileutils'
require 'minitest/autorun'

tmpdir = Dir.mktmpdir("sdd")
ADDR = File.join(tmpdir, 'sd_notify_test.sock')

Minitest.after_run do
  FileUtils.rm_r(tmpdir)
end

module SDD
  class << self
    def run(test, env)
      # TODO: Check exit code and print out data on failure
      `make test/#{test}.exe`
      Process.spawn(env, "test/#{test}.exe")
    end
  end
end

# Load tests
Dir.glob(File.expand_path("*_test.rb", __dir__)).each do |file|
  require_relative file
end
