# SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
#
# SPDX-License-Identifier: MIT

class NotifyTest < Minitest::Test
  include SDD

  def setup
    @sock = Socket.new(Socket::AF_UNIX, Socket::SOCK_DGRAM, 0)
    addr = Socket.sockaddr_un(ADDR)
    @sock.bind(addr)
  end

  def teardown
    @sock.close
    FileUtils.rm(ADDR)
  end

  def test_ignore_non_notify
    assert_equal 0, exec("simple_ready", env: {})
  end

  def test_ready
    assert_equal 0, exec("simple_ready", env: {"NOTIFY_SOCKET" => ADDR})

    msg, sender, _, anc = Timeout::timeout(5) {
      @sock.recvmsg(scm_rights: true)
    }

    assert_equal msg, "READY=1"
  end

  def test_fds_passing
    assert_equal 0, exec("fds_passing", env: {"NOTIFY_SOCKET" => ADDR})

    msg, sender, _, anc = Timeout::timeout(5) {
      @sock.recvmsg(scm_rights: true)
    }

    assert_equal msg, "FDSTORE=1"
    assert anc.cmsg_is?(:SOCKET, :RIGHTS)
  end
end
