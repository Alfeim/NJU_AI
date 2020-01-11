# NJU_AI分工

本仓库主要储存图像缺陷检测项目的代码

需要1人维护tranning_set和test_set，图像应当经过分割(分割到小尺寸)以及放大特征的预处理操作(借助ps或是其他手段)

需要1人维护Image_Process，其中应为一个预处理图像的程序/接口/脚本用以对实时输入的图像进行预处理,实现分割、特征放大的操作,并输出对应的图片作为主函数的输入

1-2人维护model和Main,主要是训练模型与搭建运行框架(目前想法基于Cpp)



# 网络模型设计

测试用例：Dog vs Cats, Flower Classifer

方案1： AlexNet  (调参可能较困难)

方案2： LeNet基础上改进(较为灵活、简单)，包括如flowers分类模型、Mnist手写分类模型，测试效果尚可

方案3： GoogleNet （理论性能最优 可以考虑后续优化 demo时期不建议，测试效果较好）

方案4:  VGG19(尚未测试)


# 更新资讯

本项目已迁移至giteas的私有仓库中https://gitea.lvsoft.dynu.net:8443/lv/defection-detection/src/branch/master/source 登陆后查看
