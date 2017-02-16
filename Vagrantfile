Vagrant.configure(2) do |config|

  config.vm.box = "ubuntu/xenial64"

  config.vm.provider "virtualbox" do |vb|
    vb.gui = false
    # Customize the amount of memory on the VM:
    vb.memory = "4096"
  end

   config.vm.provision "shell", inline: <<-SHELL
     sudo apt-get update
     sudo apt-get install -y gcc g++  
   SHELL

end
