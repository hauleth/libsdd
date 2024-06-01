# SPDX-FileCopyrightText: 2024 Łukasz Niemier <#@hauleth.dev>
#
# SPDX-License-Identifier: MIT

class NotifyTest < Minitest::Test
  def setup
    @sock = Socket.new(Socket::AF_UNIX, Socket::SOCK_DGRAM, 0)
    addr = Socket.sockaddr_un(ADDR)
    @sock.bind(addr)
  end

  def teardown
    @sock.close
    FileUtils.rm(ADDR)
    Process.wait(@pid) if @pid
  end

  def test_ready
    @pid = SDD::run(@NAME, {"NOTIFY_SOCKET" => ADDR})

    msg, sender, _, anc = @sock.recvmsg(scm_rights: true)

    assert msg == "READY=1"
  end

  def test_fds_passing
    skip "To be implemented"
  end
end
