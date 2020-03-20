# BMP 旋转

本程序可以将部分 BMP 格式的图片顺时针旋转 90° 。

## 代码说明

使用纯 C 语言完成，仅限 Windows 平台上编译运行。编译指令：
```
gcc rotatebmp.c -o rotatebmp.exe -Wno-multichar 
```
因为使用了 Windows.h 里的多字节字符，所以我选择关闭这个警告。

## 使用

```
./rotatebmp <src.bmp> <dst.bmp> [/V]
```

其中 `<src.bmp>` 为源文件，`<dst.bmp>` 为目标文件。若开启 `\V` 选项，则输出详细日志。

## 特色

- 支持更新的 DIB 头，例如 `BITMAPV4HEADER` 和 `BITMAPV5HEADER`。
- 支持 24 位色与 32 位色的旋转
- 增加 Verbose 选项用于详细输出

## 不足

- 暂时不支持低于 24 位的（需要 Color Table 的）图片
- 不支持早期 BMP 格式