#!/usr/bin/env ruby

# SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
#
# SPDX-License-Identifier: MIT

require 'fileutils'
require 'minitest/autorun'
require 'socket'
require 'timeout'
require 'tmpdir'

tmpdir = Dir.mktmpdir("sdd")
ADDR = File.join(tmpdir, 'sd_notify_test.sock')

Minitest.after_run do
  FileUtils.rm_r(tmpdir)
end

module SDD
  def exec(file, env:)
    # TODO: Check exit code and print out data on failure
    `make test/samples/#{file}.exe`
    pid = Process.spawn(env, "test/samples/#{file}.exe", unsetenv_others: true)

    _, result = Process.wait2(pid)

    result
  end
end

# Load tests
Dir.glob(File.expand_path("*_test.rb", __dir__)).each do |file|
  require_relative file
end
