Title: 例解C++测试驱动开发和单元测试
Slug: cpp-tdd-unittest
Date: 2014-10-09 23:07:31
Modified: 2014-10-09 23:07:31
Category: blog
Tags: cpp, unittest

#声明

本文翻译自Alex Ott的博客：[Test-driven development and unit testing with examples in C++](http://alexott.net/en/cpp/CppTestingIntro.html)

未经同意，请勿转载。

#测试驱动开发基础

##测试驱动开发

测试驱动开发([TDD](http://en.wikipedia.org/wiki/Test-driven_development))是一种软件开发的流程。它依赖短开发周期的多次迭代：

* 需要改进已有功能或者开发新功能时，开发人员首先编写测试案例（此刻测试案例运行失败）
* 然后实现代码使测试案例运行通过
* 最后重构代码使其符合标准

测试驱动开发与[极限编程](http://en.wikipedia.org/wiki/Extreme_programming)中的“测试先行(test-first)”概念相关，也经常与“敏捷开发”联系起来。单就测试驱动开发来说，有其[优点](http://en.wikipedia.org/wiki/Test-driven_development#Benefits)，也有[缺点](http://en.wikipedia.org/wiki/Test-driven_development#Vulnerabilities)。优缺点姑且不论，我们能在实际项目中采用这种方法提升代码质量。

TDD工作流可以描述为如下步骤的循环(参考下图)：

* 确定实现哪些功能
* 为每个功能添加单元测试案例
* 编译运行测试案例，检查是否有错误
* 实现代码以使测试通过
* 重构
* 重复运行测试，如果测试失败，修改代码
* 提交修改
* 实现下一个功能（重复以上步骤）

![测试驱动开发流程]({filename}/images/TDD.png)

##单元测试及框架

众所周知，软件测试的分类如下：

* 单元测试
* 集成测试
* 回归测试
* 验收测试
* 性能测试

本文主要讨论单元测试，但是某些技术也适用于其他测试类型。

单元测试用于测试代码单元以确保这些代码单元正常工作。代码单元是应用程序的最小可测试部分。在过程式语言中，代码单元可能是一个函数或者过程。一般来说，单元测试由开发人员完成, 其目标是隔离应用程序的各个部分，确保各个部分正确工作。单元测试可以看作是所测试代码段所必须符合的严格的书面规格。

单元测试有以下优点：

* 管理变化，应用单元测试，程序员在项目后期重构代码也能保证代码的正确性
* 简化集成，单元测试能够降低代码单元内部的不确定性，可以用在自底向上测试方法中。先测试程序的一部分，然后整体测试代码，这样使集成测试更加容易
* 单元测试可以作为系统的活文档，开发人员可以通过查看单元测试代码了解程序代码的API

###单元测试框架

通常采用单元测试框架来简化单元测试。单元测试框架应当提供如下功能：

* 新手能够简单明了地编写单元测试
* 测试框架允许老手编写复杂的测试
* 测试模块可以包含多个小的测试案例，并允许将它们组织成测试套件
* 在开发初期用户也许需要详尽的错误信息，在回归测试阶段用户只想知道是否有测试案例失败
* 对于小测试模块，执行时间和编译时间要能够匹配。测试者不希望很小的测试案例花大量时间编译
* 对于复杂的运行时间长的测试案例，测试者希望能看到测试进展情况
* 测试案例之间能够独立执行，互不影响。比如，某测试案例崩溃不会影响其它测试案例
* 简单的测试不需依赖外部库

现在几乎所有编程语言都有不只一个单元测试框架。最广泛使用的是[xUnit](http://en.wikipedia.org/wiki/XUnit)单元测试框架系列(JUnit, CppUnit, NUnit....)。xUnit单元测试框架系列易于使用，它们的功能和架构类似。xUnit单元测试框架由以下部分组成：

* 断言，检查单个条件
* 测试案例，组合多个断言，测试一组功能
* 测试套件，组合多个逻辑上互相关联的测试案例
* Fixture，配置测试案例所需的数据和状态，并在执行完成后清理。这些框架支持测试案例级的Fixture、测试套件级的Fixture、以及全局的Fixture
* 还有测试执行监控程序，用来控制测试案例的执行和收集测试案例的失败数据

###如何组织单元测试案例

一般来说，应当为所有公开暴露的函数编写单元测试，包括没有声明为static的自由函数、类的所有公有成员函数（包括公有构造函数和重载的操作符）。单元测试力求覆盖函数中的主要路径，例如不同的条件分支和循环等等。还要处理正常情况和边界情况、提供正确数据和随机数据，进而可以测试程序的错误处理逻辑。[这些文章](http://geosoft.no/development/unittesting.html)提供更多关于如何组织单元测试的建议。

测试案例通常按照某些标准组合成测试套件：共有的功能、相同功能的不同案例、共同的Fixture等等。Fixture负责配置和清除测试运行所需的数据，以使测试案例更加简短并且易于理解。

推荐采用如下方法实现测试案例：

* 一个测试案例只测试一个功能
* 简短的测试案例
* 测试能快速执行，这样才可能经常运行测试
* 测试之间互不干扰。失败的测试不能影响其它的测试
* 测试不能依赖它们的执行顺序

有些观点认为，把所有测试揉在一个大函数中能够提升代码可读性，使代码更精炼。对于这种观点有以下反对意见（在[这些文档](http://www.boost.org/doc/libs/1_45_0/libs/test/doc/html/utf/user-guide/test-organization.html)中有所提及）：

* 如果发生严重问题，或者在某些检查中抛出了异常，之后的测试案例无法被执行
* 无法只检查测试单元的某个子系统

代码可测试性还依赖于代码的设计。有时编写单元测试非常困难，因为需要测试的功能要么隐藏在复杂的接口后面，要么有很多外部依赖，因此正确组织好测试也非常困难。以下是一些关于如何编写易于单元测试的代码的建议：

* 代码应该松散耦合，类和函数的外部依赖应该尽量少；
* 避免在类或者函数内部创建复杂类的实例。此时，这些类的实例通过指针和引用传入更好，这样就可以利用Mock来测试你的代码了；
* 尽力减少类暴露的公有API，编写不同的类完成不同的任务比编写一个类完成所有任务要好。

在此[博客](http://googletesting.blogspot.com/2008/08/by-miko-hevery-so-you-decided-to.html)中可以找到更多关于编写可测试代码的建议。

##Mocking

单元测试中，Mock对象能模拟复杂、真实的对象的行为，在不可能将真实对象集成到单元测试的情况下非常有用。如果对象有下列一个特征，用Mock对象代替就非常有用：

* 产生不确定的结果（如当前时间或者温度）
* 包含很难重现的状态（如网络错误）
* 对象暂时还不存在，或者行为还会变化
* 包含只用来测试的信息和方法

Mock对象与其模仿的真实对象的接口是一致的，这样客户代码可以不用关心它使用的是一个真实对象还是一个Mock对象。许多Mock框架允许程序员指定Mock对象调用的方法和调用次序，及其传递的参数和返回值。从而如网络socket这样复杂对象的行为可以由Mock对象来模拟，程序员可以观察被测试对象对其所处于的各种状态的的回应是否正常。

典型的工作流如下：

* 掌握被测试类的接口，这样才能同时使用Mock对象和真实对象
* 用框架创建Mock类（也可以自己编写Mock类，但是一般不推荐）
* 编写用Mock对象测试的目标代码
* 创建测试案例并采用Mock对象代替真实对象。在测试案例中采取如下步骤：
  * 创建Mock类的实例
  * 设定Mock对象的行为和期望：哪些方法该调用，哪些方法不该调用，方法调用该返回什么数据，等等
  * 运行代码（这些代码使用了Mock对象）
  * 获取代码运行的结果并检查是否与期望的返回值一致，通常由Mock框架在销毁Mock对象时完成

[这里](http://alexott.net/en/cpp/CppTestingIntro.html#gmock-example)可以找到使用Google C++ Mocking框架的例子。

#C++单元测试

本节介绍C++中的单元测试和Mocking。

##C++单元测试及Boost.Test

C++有很多[单元测试框架](http://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C.2B.2B)。当前最广为使用的有Boost.Test和[Google C++测试框架](https://code.google.com/p/googletest/)。它们的功能类似，由于作者在公司项目和个人项目中使用Boost.Test，因此本文只介绍Boost.Test。

Boost.Test有这些功能：

* 初级用户和高级用户均适合使用
* 允许将测试案例组织成测试套件
* 测试案例可以自动注册也可以手动注册
* 采用参数化和类型化的测试案例测试不同的数据类型
* Fixture（资源的初始化和清除）：测试案例夹具、测试套件夹具、全局夹具
* 大量的断言和检查：
  * 异常（抛出或者没有抛出）
  * 相等、不等、大于、小于等等
  * 集合和比特位的相等测试
  * 明确的失败和成功
  * 浮点数比较，同时能够控制精度
* 不同的检查等级：warning, check, require
* 功能丰富的执行控制逻辑
* 用户定义的main过程
* 描述哪些测试应该失败
* 测试结果输出为多种格式：文本、xml、...
* 测试进度可视化
* 跨平台（支持所有平台，由Boost库支持）
* Boost许可，运行不受限制地在任何地方使用
* 上佳的[文档](http://www.boost.org/doc/libs/release/libs/test/doc/html/utf.html)和[教程](http://www.boost.org/doc/libs/release/libs/test/doc/html/utf/tutorials.html)

唯一不足的是Boost.Test缺乏Mocking功能，尽管Google Mock框架可以与它配合使用。

Boost.Test有不同的使用方法，依测试的复杂程度而定。用户可以可以自己编写测试函数然后手动注册以构建测试层次结构，也可以使用特殊的宏自动注册。

本文以“自动”测试为例，读者可以阅读[Boost.Test的在线文档](http://www.boost.org/doc/libs/release/libs/test/doc/html/utf/user-guide.html)中关于手动测试注册的内容。

通常，由Boost.Test编写的测试代码由这些对象组成：

* 测试案例，其中包含测试断言
* 测试套件，由测试案例组合而成
* Fixture，负责配置和清除测试案例、测试套件、全局环境所需相关资源和数据

[Execution monitor](http://www.boost.org/doc/libs/release/libs/test/doc/html/execution-monitor.html)执行所有单元测试：控制单元测试的执行、处理错误、收集已执行或失败的单元测试的统计数据。开发者可以通过命令行选项、环境变量、源代码控制Execution monitor的行为。

##自动注册的测试案例

对于简单单元测试，Boost.Test非常简单易用，只需包含必要的头文件，然后编写单元测试案例（或组织成测试套件），然后编译，将其与boost_unit_test_framework库链接（boost_unit_test_framework库包含负责配置和执行测试案例的main函数）。

##最简单的测试程序

这是一个最简单的测试程序，定义了一个测试案例：

``` C++

#define BOOST_TEST_MODULE Simple testcases
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(simple_test) {
  BOOST_CHECK_EQUAL(2+2, 4);
}

```

第一行声明测试的名字，第二行包含必要的头文件，第4-6行定义测试案例（`BOOST_AUTO_TEST_CASE`宏定义一个名字为`simple_test`的测试案例，案例中包含一个断言：2+2=4，断言采用`BOOST_CHECK_EQUAL`进行检查）。

编译执行该程序，屏幕上会打印如下内容（Boost.Test也可将结果输出为多种不同的格式，并且可以通过Execution Monitor的选项控制结果的详略程度）：

```

Running 1 test case...

*** No errors detected

```

如果出现错误，测试框架会在屏幕上打印如下信息：

```

Running 1 test case...
test-simple.cpp(5): error in "simple_test": check 2+2 == 5 failed [4 != 5]

*** 1 failure detected in test suite "Simple testcases"

```

以上错误信息指出了测试程序（Simple testcases）中失败案例的个数，并且指出了错误发生的位置（test-simple.cpp的第5行），同时还显示了错误的附加信息（视所采用的检查函数而定）。

##使用测试套件

当测试程序中包含大量的测试案例时，管理测试案例非常困难。Boost.Test支持将测试案例组合成测试套件，这样管理大量测试案例就非常容易了。测试套件同时还有其它优点，如为所有测试案例定义共同的Fixture，以及通过命令行选项选择执行部分测试案例。

测试套件的用法非常简单，只需将测试套件的所有测试案例写在`BOOST_AUTO_TEST_SUITE`宏（以测试套件名为参数）和`BOOST_AUTO_TEST_SUITE_END`宏之间即可：

``` C++
#define BOOST_TEST_MODULE Simple testcases 2
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(suite1)

BOOST_AUTO_TEST_CASE(test1) {
    BOOST_CHECK_EQUAL(2+2, 4);
}

BOOST_AUTO_TEST_CASE(test2) {
    BOOST_CHECK_EQUAL(2*2, 4);
}

BOOST_AUTO_TEST_SUITE_END()

``` 

编译、运行测试套件的方法与测试案例一致。

##单元测试工具及检查器

Boost.Test提供大量的[测试工具/检查器](http://www.boost.org/doc/libs/release/libs/test/doc/html/utf/testing-tools.html)。这些检查器几乎都有不同的检查级别（为了方便阅读，本文用`<level>`来代表实际的级别）：

* WARN
: 检查失败时生成警告消息，不增加失败案例统计，且测试继续
* CHECK
: 检查失败时生成错误消息并增加失败案例统计，测试继续
* REQUIRE
: 与CHECK类似，不同的是它报告的是严重的错误，检查失败时中止测试。例如用来检查代码将要使用的对象是否存在

检查器宏的基本形式是`BOOST_<level>[_check]`，只接受一个参数。唯一的例外是`BOOST_ERROR`宏和`BOOST_FAIL`宏，它们用来生成显式的错误。这是Bosst.Test检查器的[完整列表](http://www.boost.org/doc/libs/release/libs/test/doc/html/utf/testing-tools/reference.html)。

基本的宏（`BOOST_WARN`、`BOOST_CHECK`以及`BOOST_REQUIRE`）只接受一个参数，即所检查的表达式，例如：

``` C++

BOOST_WARN( sizeof(int) == sizeof(short) );
BOOST_CHECK( i == 1 );
BOOST_REQUIRE( i > 5 );

```

如果检查没有通过，Boost.Test会报告检查在源代码中的行数以及所给定的条件。用户也可用`BOOST_<level>_MESSAGE`宏报告自定义的消息。

在需要进行比较时，最好使用特殊的宏，如`BOOST_<level>_EQUAL`，`BOOST_<level>_NE`，`BOOST_<level>_GT`，等等。这些特殊宏的好处是它们会同时显示期望值和实际值，而不是只显示一句简单的失败消息（此功能也适用于用`BOOST_<level>_PREDICATE`宏定义的比较函数）。以下面的代码为例：

``` C++

int i = 2;
int j = 1;

BOOST_CHECK( i == j );
BOOST_CHECK_EQUAL( i, j );

```

第一个检查只会报告说检查失败：

```

test.cpp(4): error in "test": check i == j failed

```

而第二个检查会报告为什么检查失败以及实际的值：

```

test.cpp(5): error in "test": check i == j failed [2 != 1]

```

Boost.Test也提供了比较集合类型的特殊检查器（`BOOST_<level>_EQUAL_COLLECTION`），以及按位比较的检查器（`BOOST_<level>_BITWISE_EQUAL`）。

由于浮点数精度的问题，不能采用标准比较符号比较浮点数，但是Boost.Test提供了几个特殊的宏解决了这个问题：`BOOST_<level>_CLOSE`、`BOOST_<level>_CLOSE_FRACTION`和`BOOST_<level>_SMALL`（使用这些宏需要包含额外的头文件：boost/test/floating_point_comparison.hpp）。

在某些场合，用户还需要检查代码是否抛出异常。可用`BOOST_<level>_NO_THROW`宏检查用户代码没有抛出异常的情况。该宏接受一个表达式作为参数，对表达是求值，如果有异常抛出就根据检查等级执行相应的操作。如果要检查用户代码抛出特定异常的情况，可以使用`BOOST_<level>_THROW`宏，该宏对表达式求值（表达式作为第一个参数传入），然后检查是否抛出异常、抛出的异常的类型是否正确（异常类型作为第二个参数传入）。还有一个`BOOST_<level>_EXCEPTION`宏用来检查用户代码是否抛出异常，还提供额外的检查器以检查位于异常对象内部的数据，并返回`true`或`false`。

Boost.Test的另外一个自动化的任务是输出结果。该功能可以用来检查`<<`之类的操作符。Boost.Test提供了特殊的输出类，这些类与`std::ostream`兼容，用户可以向它们输出数据，还可获取它们的内容。此外用户还可创建包含“所需输出”的文件，并以此文件中的数据与程序代码输出的数据进行比较。

一些情况下，检查点检查也很有用（检查测试案例处于正常状态的时刻点）。Boost.Test提供了两个宏支持检查点检查：

* `BOOST_TEST_CHECKPOINT`宏，创建命名的检查点，当错误发生时输出错误消息，这在检查循环中的表达式时非常有用
* `BOOST_TEST_PASSPOINT`宏（无参数），创建匿名检查点，当错误发生时输出最后一个检查点所在的行号

##Fixture

Fixture是一类特殊的对象，用以设置和清除单元测试执行所需的数据和资源。分离Fixture和实际的测试代码能够简化单元测试，使不同的测试案例和测试套件共用一份初始化代码。

Boost.Test中的Fixture通常实现为一个类或者结构体，在其构造函数中初始化数据，在其析构函数函数中清理数据。例如：

``` C++

struct MyFixture {
  MyFixture() {
    i = new int;
    *i = 0;
  }

  ~ MyFixture() {
    delete i;
  }
  
  int* i;
};

```

可以这样使用`MyFixture`类：

``` C++

BOOST_AUTO_TEST_CASE( test_case1 )
{
  MyFixture f;
  // do something with f.i
}

```

Boost.Test同时提供了特殊的宏以简化Fixture的使用。配置测试案例可以使用`BOOST_FIXTURE_TEST_CASE`宏代替`BOOST_AUTO_TEST_CASE`宏，唯一的不同之处在于`BOOST_FIXTURE_TEST_CASE`宏有第二个参数（即Fixture对象），Fixture对象自动创建并传递给测试案例。使用宏比直接使用Fixture对象还有额外的优势，即用户能够直接访问Fixture对象的公有和保护成员，例如：

``` C++

#define BOOST_TEST_MODULE Test-case fixture example
#include <boost/test/unit_test.hpp>

struct F {
  F() : i(1) {}
  ~F() {}
  int i;
};

BOOST_FIXTURE_TEST_CASE(simple_test, F) {
  BOOST_CHECK_EQUAL(i, 1);
}

```

此例中，Fixture对象F持有一个成员变量i，它能在测试案例中直接访问。

测试套件也有类似的功能，配置测试套件可以使用`BOOST_FIXTURE_TEST_SUITE`宏代替`BOOST_AUTO_TEST_SUITE`宏。`BOOST_FIXTURE_TEST_SUITE`宏以测试套件对象为第二个参数，且为测试套件中的每个测试案例分别生成一个Fixture对象。需要记住的是：对每个测试案例/测试套件，都会创建一个新的Fixture对象，测试案例中的Fxiture对象的状态改变不会改变其它测试案例。

Boost.Test还支持第三种Fixture对象（即全局Fixture），用来进行全局数据的设置/清理。可以使用`BOOST_GLOBAL_FIXTURE`宏创建全局环境中的的Fixture，传入Fixture的名字作为参数。在第一个测试案例开始前创建Fixture，在最后一个测试案例执行之后销毁。

##Output of results

##Execution control

#C++Mocking框架

#更多资料
关于TDD的资料,包括书籍、课程、文章等等：

* 书籍：
  * Kent Beck. [Test-driven development: By example](http://www.amazon.com/gp/product/0321146530?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0321146530)
  * David Astels. [Test Driven Development: A Practical Guide](http://www.amazon.com/gp/product/0131016490?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0131016490)
  * Robert C. Martin. [Clean Code: A Handbook of Agile Software Craftsmanship](http://www.amazon.com/gp/product/0132350882?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0132350882) - 本书主要面向Java程序员
  * Michael Feathers. [Working Effectively with Legacy Code](http://www.amazon.com/gp/product/0131177052?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0131177052)
  * Martin Fowler, Kent Beck, John Brant, William Opdyke, Don Roberts. [Refactoring: Improving the Design of Existing Code](http://www.amazon.com/gp/product/0201485672?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0201485672)
  * Steve Freeman, Nat Pryce. [Growing Object-Oriented Software, Guided by Tests](http://www.amazon.com/gp/product/0321503627?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0321503627)
  * Steve McConnell. [Code Complete, 2ed](http://www.amazon.com/gp/product/0735619670?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0735619670) - 内容包含很多代码设计方面的建议，其中一章专门介绍单元测试和其它测试
  * Paul Hamill. [Unit Test Frameworks](http://www.amazon.com/gp/product/0596006896?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0596006896)
  * James Shore. [The Art of Agile Development](http://www.amazon.com/gp/product/0596527675?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0596527675)
  * 极限编程系列：
    * Kent Beck, Cynthia Andres. [Extreme Programming Explained: Embrace Change, 2ed](http://www.amazon.com/gp/product/0321278658?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0321278658)
    * Kent Beck, Martin Fowler. [Planning Extreme Programming](http://www.amazon.com/gp/product/0201710919?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0201710919)
    * Ron Jeffries, Ann Anderson, Chet Hendrickson. [Extreme Programming Installed](http://www.amazon.com/gp/product/0201708426?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0201708426)
    * Lisa Crispin, Tip House. [Testing Extreme Programming](http://www.amazon.com/gp/product/0321113551?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0321113551)
    * Ken Auer, Roy Miller. [Extreme Programming Applied: Playing to Win](http://www.amazon.com/gp/product/0201616408?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0201616408)
  * Java语言：
    * Petar Tahchiev, Felipe Leme, Vincent Massol, Gary Gregory. [JUnit in Action, 2ed](http://www.amazon.com/gp/product/1935182021?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=1935182021)
    * J.B. Rainsberger. [JUnit Recipes: Practical Methods for Programmer Testing](http://www.amazon.com/gp/product/1932394230?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=1932394230)
    * Kent Beck. [JUnit Pocket Guide](http://www.amazon.com/gp/product/0596007434?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=0596007434)
    * Lasse Koskela. [Test Driven: TDD and Acceptance TDD for Java Developers](http://www.amazon.com/gp/product/1932394850?ie=UTF8&tag=aleottshompag-20&linkCode=as2&camp=1789&creative=390957&creativeASIN=1932394850)
* 在线资源：
  * [StackOverflow上关于单元测试的内容](http://stackoverflow.com/questions/tagged/unit-testing)
  * [Google Testing Blog](http://googletesting.blogspot.com/)
  * Wiki at [c2.com](http://c2.com/cgi/wiki?UnitTest)
  * [Practical Testing](http://www.lenholgate.com/blog/2004/05/practical-testing.html) — 测试主题系列博客