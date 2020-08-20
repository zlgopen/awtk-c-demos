# awtk-c-demos

AWTK各个控件的示例代码(C语言版本)

## 准备

1.获取awtk并编译

```
git clone https://github.com/zlgopen/awtk.git
cd awtk; scons; cd -
```

2.获取awtk-c-demos并编译
```
git clone https://github.com/zlgopen/awtk-c-demos.git
cd awtk-c-demos
```

* 生成资源

```
python ./scripts/update_res.py all
```

> 或者通过 designer 生成资源


* 编译PC版本

```
scons
```

* 编译LINUX FB版本

```
scons LINUX_FB=true
```

> 完整编译选项请参考[编译选项](https://github.com/zlgopen/awtk-widget-generator/blob/master/docs/build_options.md)


## 运行

```
./bin/demo_xxxx
```

>请把demo\_xxxx换成具体的程序。

## 示例代码

请参考：demos

> 本文以Linux/MacOS为例，Windows可能会微妙差异，请酌情处理。
