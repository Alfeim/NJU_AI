# 1.首先从ubuntu官方下载镜像     https://ubuntu.com/download/desktop(推荐18.04)

# 2.制作U盘启动盘,推荐工具Rufus  https://rufus.ie/zh_CN.html

  制作方法:选择安装系统镜像，分区选择GPT，目标系统UEFI，之后点击开始，等待进度条走完，然后点击[关闭]，弹出U盘.

# 3.安装系统

# 4.安装Nidia显卡驱动

  首先安装好vim，打开/etc/modprobe.d/blacklist.conf，在末尾键入以下几行以禁用原本的一些显卡驱动
  blacklist vga16fb
  blacklist nouveau
  blacklist rivafb
  blacklist rivatv
  blacklist nvidiafb
  键入完毕,保存,输入命令sudo update-initramfs -u以更新
  然后重启电脑,进入BIOS禁用掉secure boot，重启进入系统后发现分辨率已经变低了说明以上步骤成功
  
  接下来,打开终端,键入以下命令以更新驱动源
  sudo apt-get purge nvidia*(删除原有的N卡驱动)
  sudo add-apt-repository ppa:graphics-drivers/ppa
  sudo apt-get update
  ubuntu-drivers devices
  
  然后打开软件与更新,在附加驱动中选择适合的显卡驱动,点击更改,等待安装完成.
  完成后重启系统,此时发现系统分辨率已经正常,打开终端输入nvidia-settings弹出界面且输入nvidia-smi打印出显卡信息说明安装成功

# 5.安装cuda与cudnn

  此步骤可以按照tensorflow官网的流程进行(点击GPU支持,查看ubuntu18.04的安装方式,可以省略掉安装Nvidia驱动的步骤因为我们已经安装过了)
  需要注意的是,在最后一步sudo apt-get update 后,如果直接输入sudo apt-get install -y --no-install-recommends libnvinfer-dev=5.1.5-1+cuda10.0会出现
  依赖不满足的问题,解决方法是分两步,也就是
  
  sudo apt-get install -y --no-install-recommends libnvinfer5=5.1.5-1+cuda10.0
  sudo apt-get install -y --no-install-recommends libnvinfer-dev=5.1.5-1+cuda10.0
   
  然后等待安装完即可.
  
  安装完毕后,在 ～/.bashrc中添加几行
  export PATH=/usr/local/cuda-10.0/bin${PATH:+:${PATH}}
  export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
  export CUDA_HOME=/usr/local/cuda
  保存,输入source ~/.bashrc更新即可 
 
   
  随后可以打开 /usr/local/cuda-10.0/samples/1_Utilities/deviceQuery目录,在该目录下直接make会生成可执行文件,如果该文件可以正常运行说明cuda已经
  安装成功

# 6.安装anaconda

  直接去anaconda官方网站下载,用bash命令运行下载下来的安装文件即可
  安装成功后,为了给予其可创建虚拟环境的权限,需要键入以下命令
  
  sudo chown -R $USER:$USER 自己的anaconda3目录
  
  然后利用就可以创建自己的虚拟环境了！

# 7.在虚拟环境中安装tensorflow

  在创建虚拟环境前,记得先更新anconda的源,推荐使用清华源,直接键入以下命令
  conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
  conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
  conda config --set show_channel_urls yes
  
  同时,为pip更换阿里源,按照以下方式键入命令
  mkdir ~/.pip
  cat > ~/.pip/pip.conf << EOF
  然后键入以下四行
  [global]
  trusted-host=mirrors.aliyun.com
  index-url=https://mirrors.aliyun.com/pypi/simple/
  EOF
  
  随后用conda create -n 环境名 python=版本号 来创建虚拟环境,推荐版本号是3.6
  创建完成后,用 source activate 环境名 来激活并进入虚拟环境
  进入虚拟环境后,只需要按照tensorflow官网的步骤,直接键入 pip install --ignore-installed --upgrade tensorflow-gpu 即可通过pip方式安装
  安装成功后,按照官网给的方法验证即可！


# ps.如果在import tensorflow as tf后出现了类似 FutureWarning: Passing (type, 1) 的信息,说明环境中numpy版本过高了,可以通过降级方式解决
  
  输入查看环境中numpy的版本号, 键入pip show numpy发现版本号过高(比如1.17)
  输入pip uninstall numpy以卸载当前的numpy
  输入pip install numpy==1.16.4安装低版本的numpy,问题解决
  
# 8.安装keras
  在虚拟环境中执行 pip install keras
  
# 9.安装pytorch
  新建一个虚拟环境,执行conda install pytorch torchvision -c pytorch
 
  
  
  
  




  

  
