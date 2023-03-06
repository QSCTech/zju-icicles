# 机器学习中的矩阵、向量求导

## 我的阅读总结 ##
1. 矩阵运算本来就是一堆数字两两求导，规定其维度只对最后$x+=grad*\nabla x $和链式法则传播时候有用
2. layout在wiki指的是$\part \frac{y}{x}$看作$\frac{y^T}{x} or\frac{y}{x^T}$。numeator是分子做行数。
3. 规定vec对数字还是原型，vec对vec 是上×下。这样在梯度下降的更新步骤上是一致的、可计算的。
4. 中间传播兼容性：只要头和尾的组合可导，那中间一定要传播过去。假设一下各个维度都不同，只要链式法则、乘法规律满足，结果必对（怎么说也就差一个转置，只要控制住两头，肯定没问题）
5. 碰上链式中间的数字可以化成1-D vector。对于vec，可以只看作是m维，不关心1*m or m\*1

## 写在前面

本文的目标读者是想快速掌握矩阵、向量求导法则的学习者，主要面向矩阵、向量求导在机器学习中的应用。因此，本教程而非一份严格的数学教材，而是希望帮助读者尽快熟悉相关的求导方法并在实践中应用。在介绍向量求导公式时，本教程中会出现少量证明，但这些证明都很简单，其目的是辅助公式的记忆、提供向量导数计算的实例，请读者不要跳过。另外，本教程假定读者熟悉一元函数的求导。

所谓**矩阵求导，本质上只不过是多元函数求导**，仅仅是把函数的自变量以及求导的结果排列成了矩阵的形式，方便表达与计算而已。类似地，复合函数的求导法则本质上也是多元函数求导的链式法则，只是将结果整理成了矩阵的形式。从原理上讲，可以对矩阵的每个分量逐元素地求导，得到最终结果；但是这样做太繁琐，极其容易出错，因此推导并记住一些常用的结论在实践中是非常必要的。



矩阵求导本身有很多争议，例如：

- 对于求导结果是否需要转置？
  - 不同教材对此处理的结果不一样，这属于不同的 [Layout Convention](https://en.wikipedia.org/wiki/Matrix_calculus#Layout_conventions)。本文**以不转置为准**，即求导结果与原矩阵/向量同型，术语叫 Mixed Layout。
- 矩阵对向量、向量对矩阵、矩阵对矩阵求导的结果是什么？
  - 最自然的结果当然是把结果定义成三维乃至四维张量，但是这并不好算。也有一些绕弯的解决办法（例如把矩阵抻成一个向量等），但是这些方案都不完美（例如复合函数求导的链式法则无法用矩阵乘法简洁地表达等）。在本教程中，我们认为，**这三种情形下导数没有定义**。凡是遇到这种情况，都通过其他手段来绕过，后面会有具体的示例。

因此，本教程的符号体系有可能与其他书籍或讲义不一致，求导结果也可能不一致（例如相差一次矩阵转置，或者是结果矩阵是否平铺成向量等），使用者需自行注意。另外，本教程中有很多笔者自己的评论，例如关于变形的技巧、如何记忆公式、如何理解其他的教程中给出的和本教程中形式不同的结果等。

文中如有错漏，请联系 ruanchong_ruby@163.com，我会尽快订正。





## 符号表示

#### 变量使用规范

- 标量用普通小写字母或希腊字母表示，例如 $t,\alpha$
- 向量用粗体小写字母表示，例如 $\boldsymbol{x}$，其元素记作 $x_i$（注意这里 $x$ 没有加粗。加粗的小写字母加下标，例如 $\boldsymbol{x}_1, \boldsymbol{x}_2$ 等，表示这是两个不同的向量）。**向量默认为列向量**，行向量需要用列向量的转置表示，例如 $\boldsymbol{x}^T$ 等
- 矩阵用大写字母表示，如 $A$ 等，其元素记作 $a_{ij}$（注意这里 $a$ 用的是小写字母。大写字母加下标，例如 $A_1, A_2$ 等，表示不同的常数矩阵）
- 字母表中靠前的字母（如 $a, b, c$ 等）表示常量，$f, g, h$ 或字母表中靠后的字母（如 $u, v$ 等）等表示变量或函数
- 有特殊说明的除外



#### 导数符号

- 若 $f$ 是关于 $x$ 的函数，则 $f$ 对 $x$ 的导数记作 $\partial{f}/\partial{x}$ 或  $\nabla_x f$；若待求导的变量比较明确，也可以省略下标记作 $\nabla f$
- 上一条中的 $f$ 和 $x$ 可以指代任意维度的变量





## 导数定义

以前一节规定的符号为基础，根据函数值和自变量的类型，本文对求导结果及其维度进行如下约定：

- 矩阵/向量值函数对实数的导数
  - 要点：求导结果与函数值同型，且每个元素就是函数值的相应分量对自变量 $x$ 求导
  - 若函数 $F:\mathbb{R}\rightarrow \mathbb{R^{m\times n}}$，则 $\partial{F}/\partial{x}$ 也是一个 $m\times n$ 维矩阵，且 $(\partial{F}/\partial{x})_{ij} = \partial{f_{ij}}/\partial{x}$。导数也可记作 $\nabla_x F$ 或 $F'_x$。
  - 由于向量是矩阵的特殊情形，根据上面的定义也可以得到函数值为列向量时的定义：若有函数 $\boldsymbol{f}:\mathbb{R}\rightarrow \mathbb{R^{m}}$，则 $\partial{\boldsymbol{f}}/\partial{x}$ 也是一个 $m$ 维列向量，且 $(\partial{\boldsymbol{f}}/\partial{x})_i = \partial{f_i}/\partial{x}$。若函数值为行向量 $\boldsymbol{f}^T$，则相应的求导结果 $\partial{\boldsymbol{f}^T}/\partial{x}$ 也是行向量。
  - 注：本文开头即说明过，变量为向量时仅仅是将其看作多个实数，无所谓行向量与列向量之分。这里规定结果形如行向量或列向量，仅仅为了把公式用矩阵相乘的方式表示出来，进而与其他部分进行矩阵运算。下同。
- 实值函数对矩阵/向量的导数
  - 要点：求导结果与自变量同型，且每个元素就是 $f$ 对自变量的相应分量求导
  - 这是最重要的一个类别，因为机器学习里一般都是求标量损失函数对向量/矩阵参数的导数
  - 若函数$f:\mathbb{R^{m\times n}}\rightarrow \mathbb{R}$，则 $\partial{f}/\partial{X}$ 也是一个 $m\times n$ 维矩阵，且 $(\partial{f}/\partial{X})_{ij} = \partial{f}/\partial{x_{ij}}$。导数也可使用劈形算子记作 $\nabla_{X} f$。
  - 由于向量是矩阵的特殊情形，根据上面的定义也可以得到自变量为列向量时的定义：若函数 $f:\mathbb{R^{m}}\rightarrow\mathbb{R}$，则 $\partial{f}/\partial{\boldsymbol{x}}$ 也是一个 $m$ 维列向量，且 $(\partial{f}/\partial{\boldsymbol{x}})_i = \partial{f}/\partial{x_i}$。若自变量是行向量 $\boldsymbol{x}^T$，则结果 $\partial{f}/\partial{\boldsymbol{x}^T}$ 也是行向量。
- 向量值函数对向量的导数（**雅克比矩阵**）
  - 若函数 $\boldsymbol{f}:\mathbb{R^{n}}\rightarrow\mathbb{R^{m}}$，则 $\partial{\boldsymbol{f}}/\partial{\boldsymbol{x}}$ 是一个 $m\times n$ 维矩阵，且 $(\partial{\boldsymbol{f}}/\partial{\boldsymbol{x}})_{ij} = \partial{f_i}/\partial{x_j}$。用劈形算子表示时可记作 $\nabla_{\boldsymbol{x}} \boldsymbol{f}$。
  - 注：如前所述，本教程仅仅是把变量都看成多个实数，无所谓行与列之分，因此在表述从向量 $\boldsymbol{x} \in \mathbb{R}^n$ 到 $\boldsymbol{f} \in \mathbb{R}^m$ 的雅克比矩阵时，不区分 $\boldsymbol{x}$ 或者 $\boldsymbol{f}$ 到底是行向量还是列向量（正都是根据 $n$ 个实数计算出 $m$ 个实数），统一用 $\nabla_{\boldsymbol{x}} \boldsymbol{f}$ 表示，维度也都是 $m\times n$。有些教程可能会区分行对列、列对列、行对行、列对行几种不同情形的求导，认为其中有些结果相差一个转置，有些组合不能求导等等。本教程则认为上述各种情形的求导结果都相同，就是雅克比矩阵。
  - 特别地，若 $\boldsymbol{f}$ 退化成标量 $f$，则 $\boldsymbol{x}$ 到 $\boldsymbol{f}$ 的雅克比矩阵 $\dfrac{\partial{\boldsymbol{f}}}{\partial{\boldsymbol{x}}}$ 是一个行向量，是梯度（列向量）的转置，即 $ \dfrac{\partial{\boldsymbol{f}}}{\partial{\boldsymbol{x}}} = \left(\dfrac{\partial{f}}{\partial{\boldsymbol{x}}}\right)^T$。注意这里使用的记号：左边 $\boldsymbol{f}$ 加粗，是把它看做一个长度为 1 的向量，表示求向量 $\boldsymbol{x}$ 到向量 $\boldsymbol{f}$ 的雅克比矩阵；右边 $f$ 为普通字体，表示实函数 $f$ 对向量 $\boldsymbol{x}$ 的导数。
- 关于劈形算子 $\nabla$ 和 Hessian 矩阵的补充
  - 劈形算子和偏导数两种记号大体上是相同的，只不过在涉及到变量分量的推导过程（例如用链式法则推神经网络的BP算法）中，偏导数那一套符号更加常用；而劈形算子的优势是书写简单，在对传统的机器学习模型的目标函数求导时，劈形算子有时更常用。
  - 对于一个实函数 $f:\mathbb{R^{m}}\rightarrow\mathbb{R}$，其梯度记为 $\nabla f = \dfrac{\partial{f}}{\partial{\boldsymbol{x}}}$，也可记作 $\textbf{grad} f$，是一个 $m$ 维向量。Hessian矩阵是一个 $m\times m$ 的矩阵，记为 $\nabla^2 f$，其中 $(\nabla^2 f)_{ij} = \dfrac{\partial^2 f}{\partial x_i \partial x_j}$。根据上述定义可以发现，Hessian 矩阵其实是 $\boldsymbol{x}$ 到 $\nabla f$ 的雅克比矩阵，因此 $\nabla^2 f$ 不光是一个形式记号，而是可以用 $\nabla^2 f = \nabla (\nabla f)$ 来计算。
    - 注：某些教材区分对行向量和列向量求导，认为 Hessian 矩阵是先对行向量 $\boldsymbol{x}^T$ 求导，再对列向量 $\boldsymbol{x}$ 求导（或者反过来），因此写作 $\dfrac{\partial^2 f}{\partial \boldsymbol{x} \partial{\boldsymbol{x}^T}}$（或者 $\dfrac{\partial^2 f}{\partial \boldsymbol{x}^T \partial{\boldsymbol{x}}}$）。
  - 对于一个实函数 $f:\mathbb{R^{m\times n}}\rightarrow\mathbb{R}$，其梯度规定为 $m\times n$ 维矩阵 $\nabla f =  \dfrac{\partial{f}}{\partial{X}}$，Hessian矩阵不作定义。





## 对上述约定的理解

- 对于实值函数 $f$，上面的导数定义符合转置关系，即 $\nabla_{x}f$ 和 $\nabla_{x^T}f$ 互为转置
  - $\nabla_{x}f = (\nabla_{x^T}f)^T$（其中 $x$ 代表任意维度的向量或矩阵）
- 函数增量的线性主部与自变量增量的关系
  - 实值函数对矩阵的导数
    - $\delta f \approx \sum_{i,j}(\nabla_X f)_{ij} (\delta X)_{ij} = tr((\nabla_X f)^T \delta X) $
      - 此式用到的技巧非常重要：**两个同型矩阵对应元素相乘再求和时常用上面第二个等式转化为迹**，从而简化公式表达和运算
      - 从另一个角度讲，这是矩阵导数的另一种定义。即：对于函数 $f(X):\mathbb{R^{m\times n}}\rightarrow \mathbb{R}$，若存在矩阵$A$，使得 $||\delta X||\rightarrow 0$时（$||\cdot||$ 为任意范数），成立 $\delta f = tr(A^T\delta X) + o(||\delta X||)$，则定义$\nabla f = A$
      - **矩阵乘积的迹是一个线性算子**。事实上，如果有两个同型矩阵 $A, B$，他们的内积即定义为 $\langle A, B\rangle = tr(A^TB)$。容易验证矩阵内积是向量内积的推广（定义都是对应元素相乘再求和）
  - 实值函数对向量的导数
    - $\delta f \approx (\nabla_\boldsymbol{x} f)^T \delta\boldsymbol{x} $
      - 上式右边是向量内积
  - 向量值函数对向量的导数
    - $\delta \boldsymbol{f} \approx (\nabla_{\boldsymbol{x}} \boldsymbol{f}) \delta\boldsymbol{x} $
      - 此式即为重积分换元时用于坐标变换的Jacobian矩阵。



## 变量多次出现的求导法则

> 若某个变量在函数表达式中多次出现，可以单独计算函数对自变量的每一次出现的导数，再把结果加起来。

这条规则很重要，尤其是在推导某些共享变量的模型的导数时很有用，例如 autoencoder with tied weights（编码和解码部分的权重矩阵互为转置的自动编码器）和卷积神经网络（同一个 feature map 中卷积核的权重在整张图不同位置共享）等。

举例（本例中 $x$ 是标量，但该规则对向量和矩阵也是成立的）：假设函数表达式是 $f(x) = (2x+1)x + x^2$，可以先把三个 $x$ 看成三个不同的变量，即把 $f$ 的表达式看成 $(2x_1+1)x_2 + x_3^2$，然后分别计算 $\partial f/\partial x_1 = 2x_2$，$\partial f/\partial x_2 = 2x_1 + 1$，和 $\partial f/\partial x_3 = 2x_3$，最后总的导数就是这三项加起来：$2x_2 + (2x_1 + 1) + 2x_3$，此时再把 $x$ 的下标抹掉并化简，就得到 $6x+1$。熟悉这个过程之后，可以省掉添加下标再移除的过程。

如果用计算图（computation graph，描述变量间依赖关系的示意图，后面会举例）的语言来描述本条法则，就是：**若变量 $x$ 有多条影响函数 $f$ 的值的路径，则计算 $\partial f / \partial x$ 时需要对每条路经求导最后再加和。** 如果想更多地了解计算图和反向传播，推荐阅读 [Colah 君的文章](http://colah.github.io/posts/2015-08-Backprop/)。其中详细讲述了计算图如何工作，不仅讲反向传播还讲了前向传播（前向传播对于目前的机器学习算法来说似乎没有太大的用处，但是对于加深计算图的理解很有帮助。RNN 曾经有一种学习算法叫 RTRL 就是基于前向传播的，不过近年来不流行了，被 BPTT 取代了）。

有了上面的基础，我们就可以推导 Batch normalization（以下简称 BN）的求导公式了。 BN 的计算过程为：

![BN-forward](BN-Forward.PNG)

其中 $m$ 是批的大小，$x_1$ 到 $x_m$ 分别是 $m$ 个不同样本对于某个神经元的输入，$l$ 是这个批的总的损失函数，所有变量都是标量。求导的第一步是画出变量依赖图，如下所示（根据左边的变量可以计算出右边的变量，如果为了强调，也可以在边上添加从左向右的箭头）：

![BN-computation-graph](BN-computation-graph.PNG) 

左侧，右上，右下分别是三种不同的画法

- 左边的图是把所有变量 $x_i$ 都画了出来，比较清楚，如果想不清楚变量之间是如何相互依赖的，这样画可以帮助梳理思路

- 右上是我自创的一种方法，借鉴了概率图模型中的盘记号（plate notation），把带下标的变量用一个框框起来，在框的右下角指明重复次数；右下不是完整的计算图，仅仅是其中一个局部，是为了说明在有些资料绘制的计算图中，相同的变量（如本例中的 $\mu_B$）只出现一次，从而图中会出现环

  - 在这种表示法中，如果要求 $\dfrac{\partial \sigma_B^2}{\partial x_i}$，需要对 $x_i \rightarrow \sigma_B^2$ 和 $x_i \rightarrow \mu_B \rightarrow \sigma_B^2$ 这两条路径求导的结果做加和

- 这几种计算图的表示法没有本质区别，读者也可以尝试其他可能的画法，自己看着舒服就行


BN 原论文中给出了反向传播的公式，不过这里我们不妨试着自己手算一遍，加深对计算图的理解。下面的计算暂时不涉及向量/矩阵的求导，只是正常的多元函数求偏导，读者可以放心自己动手算：

- $\hat{x}_i$ 影响损失函数只有唯一的路径 $\hat{x}_i \rightarrow y_i \rightarrow l$
  - 根据链式法则，得到：$\dfrac{\partial l}{\partial \hat{x}_i} = \dfrac{\partial l}{\partial y_i} \dfrac{\partial y_i}{\partial \hat{x}_i} = \dfrac{\partial l}{\partial y_i} \gamma$。

*  $\gamma$ 影响损失函数有 $m$ 条路径：$\forall i$，$\gamma \rightarrow y_i \rightarrow l$ 都是一条路径，需要对这些路径分别求导再加和
   *  $\dfrac{\partial l}{\partial \gamma} = \sum_i \dfrac{\partial l}{\partial y_i} \dfrac{\partial y_i}{\partial \gamma} = \sum_i\dfrac{\partial l}{\partial y_i} \hat{x}_i$
*  $\dfrac{\partial l}{\partial \beta}$ 的计算与之类似，结果为 $\dfrac{\partial l}{\partial \beta} = \sum_i \dfrac{\partial l}{\partial y_i}\dfrac{\partial y_i}{\partial \beta} = \sum_i \dfrac{\partial l}{\partial y_i} \cdot 1 = \sum_i \dfrac{\partial l}{\partial y_i}$。
*  $\sigma_B^2$ 影响损失函数的路径也有 $m$ 条：$\forall i, \sigma_B^2 \rightarrow \hat{x}_i \rightarrow l$
   *  此处忽略中间变量 $y_i$，直接把 $l$ 看成的 $\hat{x}_i$ 函数
   *  据此有 $\dfrac{\partial l}{\partial \sigma_B^2} = \sum_i \dfrac{\partial l}{\partial \hat{x}_i} \dfrac{\partial \hat{x}_i}{\partial \sigma_B^2} = \sum_i \dfrac{\partial l}{\partial \hat{x}_i} \cdot -\dfrac{1}{2}(x_i - \mu_B)(\sigma_B^2+\epsilon)^{-3/2}$。注意求导的时候把 $\sigma_B^2$ 当成一个整体，想象这就是一个字母，而不要把它想成标准差的平方。
*  $\mu_B$ 影响 $l$ 共有 $2m$ 条路径：$\forall i, \mu_B \rightarrow \hat{x}_i \rightarrow l, \mu_B \rightarrow \sigma_B^2 \rightarrow l$（分别对应于右上图中较短和较长的路径）
   *  所以 $\dfrac{\partial l}{\partial \mu_B} = \sum_i (\dfrac{\partial l}{\partial \hat{x}_i} \dfrac{\partial \hat{x}_i}{\partial \mu_B} + \dfrac{\partial l}{\partial \sigma_B^2} \dfrac{\partial \sigma_B^2}{\partial \mu_B})$
   *  又因为 $\dfrac{\partial \sigma_B^2}{\partial \mu_B}=\dfrac{-2}{m}\sum_j (x_j-\mu_B)=0$，上式可以化简为 $\dfrac{\partial l}{\partial \mu_B} = \sum_i \dfrac{\partial l}{\partial \hat{x}_i} \dfrac{\partial \hat{x}_i}{\partial \mu_B}=\sum_i \dfrac{\partial l}{\partial \hat{x}_i} \dfrac{-1}{\sqrt{\sigma_B^2+\epsilon}}$
*  $\forall i, x_i$ 影响损失函数有 $3$ 条路径：$x_i \rightarrow \hat{x}_i \rightarrow l, x_i \rightarrow \sigma_B^2 \rightarrow l, x_i \rightarrow \mu \rightarrow l$
   *  故 $$ \begin{align*} 
   \dfrac{\partial l}{\partial x_i} & = & \dfrac{\partial l}{\partial \hat{x}_i} \dfrac{\partial \hat{x}_i}{\partial x_i} + \dfrac{\partial l}{\partial \sigma_B^2} \dfrac{\partial \sigma_B^2}{\partial x_i} + \dfrac{\partial l}{\partial \mu_B} \dfrac{\partial \mu_B}{\partial x_i} \\
    & = & \sum_i \dfrac{\partial l}{\partial \hat{x}_i} \dfrac{1}{\sqrt{\sigma_B^2+\epsilon}} + \dfrac{\partial l}{\partial \sigma_B^2} \dfrac{2}{m}(x_i - \mu_B) + \dfrac{\partial l}{\partial \mu_B} \dfrac{1}{m}
    \end{align*}$$





## 常用公式



#### 向量求导的链式法则

- 易发现**雅克比矩阵的传递性**：若多个向量的依赖关系为 $\boldsymbol{u} \rightarrow \boldsymbol{v} \rightarrow \boldsymbol{w}$，则：$\dfrac{\partial \boldsymbol{w}}{\partial \boldsymbol{u}} = \dfrac{\partial \boldsymbol{w}}{\partial \boldsymbol{v}}  \dfrac{\partial \boldsymbol{v}}{\partial \boldsymbol{u}}$。
  - 证明：只需逐元素求导即可。$\dfrac{\partial w_i}{\partial u_j} = \sum_k \dfrac{\partial w_i}{\partial v_k} \dfrac{\partial v_k}{\partial u_j}$，即 $\dfrac{\partial \boldsymbol{w}}{\partial \boldsymbol{u}}$ 的 $(i, j)$ 元等于矩阵 $\dfrac{\partial \boldsymbol{w}}{\partial \boldsymbol{v}}$ 的 $i$ 行 和 矩阵 $\dfrac{\partial \boldsymbol{v}}{\partial \boldsymbol{u}}$ 的第 $j$ 列的内积，这正是矩阵乘法的定义。
  - 注：**将两项乘积的和转化成向量内积或矩阵相乘来处理，是很常用的技巧。**
- 雅克比矩阵的传递性可以很容易地推广到多层中间变量的情形，采用数学归纳法证明即可。
- 若中间变量都是向量，但最后的结果变量是一个实数，例如变量依赖关系形如 $\boldsymbol{x} \rightarrow \boldsymbol{v} \rightarrow \boldsymbol{u} \rightarrow f$，则：
  - 由雅克比矩阵的传递性知：$\dfrac{\partial \boldsymbol{f}}{\partial \boldsymbol{x}} = \dfrac{\partial \boldsymbol{f}}{\partial \boldsymbol{u}}  \dfrac{\partial \boldsymbol{u}}{\partial \boldsymbol{v}} \dfrac{\partial \boldsymbol{v}}{\partial \boldsymbol{x}}$。再根据 $\boldsymbol{f}$ 退化为实数时雅克比矩阵和函数导数的关系，有：$\dfrac{\partial \boldsymbol{f}}{\partial \boldsymbol{x}} = \dfrac{\partial f}{\partial \boldsymbol{x}^T}, \dfrac{\partial \boldsymbol{f}}{\partial \boldsymbol{u}} =  \dfrac{\partial f}{\partial \boldsymbol{u}^T}$。以上三式相结合，可以得到如下链式法则：$\dfrac{\partial f}{\partial \boldsymbol{x}^T} = \dfrac{\partial f}{\partial\boldsymbol{u}^T} \dfrac{\partial\boldsymbol{u}}{\partial\boldsymbol{v}} \dfrac{\partial\boldsymbol{v}}{\partial\boldsymbol{x}} $
  - 此公式是把导数视为行向量（即以 $\dfrac{\partial f}{\partial \boldsymbol{x}^T}$ 和 $\dfrac{\partial f}{\partial \boldsymbol{u}^T}$ 的形式）给出的。如果需要把导数视为列向量，只需将公式两边同时转置即可
  - 上述结果显然也可以推广到任意多层复合的情形（可用于 RNN 的 BPTT 的推导）
- 作为特例，若中间只经过一次复合 $\boldsymbol{x} \rightarrow \boldsymbol{u} \rightarrow f$，求导公式如下：
  - $\dfrac{\partial f}{\partial \boldsymbol{x}} = \left(\dfrac{\partial\boldsymbol{u}}{\partial\boldsymbol{x}}\right)^T \dfrac{\partial f}{\partial\boldsymbol{u}}$，或写作 $\nabla_{\boldsymbol{x}} f = (\nabla_{\boldsymbol{x}} \boldsymbol{u})^T \; \nabla_{\boldsymbol{u}} f$
  - 进一步地，假如 $\boldsymbol{u}$ 和 $\boldsymbol{x}$ 维度相同且 $u_i$ 仅由 $x_i$ 计算出，则易知 $\dfrac{\partial \boldsymbol{u}}{\partial \boldsymbol{x}}$ 是对角阵，上面的公式可以化简为：$\dfrac{\partial f}{\partial \boldsymbol{x}} = \text{vec}\left(\dfrac{\partial\boldsymbol{u}}{\partial\boldsymbol{x}}\right) \odot \dfrac{\partial f}{\partial\boldsymbol{u}}$，其中 $\text{vec}(D)$ 表示取对角矩阵 $D$ 的对角线上的元素组成列向量，$\odot$ 表示两个向量逐元素相乘。由于最终的结果是两个向量逐元素相乘，所以也可以交换一下两项相乘的顺序，写成：$\dfrac{\partial f}{\partial \boldsymbol{x}} = \dfrac{\partial f}{\partial\boldsymbol{u}} \odot \text{vec}\left(\dfrac{\partial\boldsymbol{u}}{\partial\boldsymbol{x}}\right)$。
    - 上述公式的另一种推导方式是直接根据导数的定义逐分量地计算：$\dfrac{\partial f}{\partial x_i} = \sum_k \dfrac{\partial f}{\partial u_k} \dfrac{\partial u_k}{\partial x_i} = \dfrac{\partial f}{\partial u_i} \dfrac{\partial u_i}{\partial x_i}$（此式为上式的分量形式）
  - 这种 $u_i$ 仅依赖 $x_i$ 而与其他 $x_j$ 无关的情形在神经网络中很常见，包括但不限于
    - 逐元素地应用激活函数：$\boldsymbol{z} \rightarrow \boldsymbol{a} = \sigma(\boldsymbol{z}) \rightarrow l$
    - 现代 RNN 单元中的门限操作（以 LSTM 为例）：$c_{t-1} \rightarrow c_t = f_t \odot c_{t-1} + (1-f_t)\odot \hat{c}_t \rightarrow l$
- 记忆方法：只需记住结果是一堆雅克比矩阵的乘积，相乘的顺序根据**维度相容原则**调整即可（假设每个中间变量的维度都不一样，看怎么摆能把雅克比矩阵的维度摆成矩阵乘法规则允许的形式。只要把矩阵维度倒腾顺了，公式也就对了。）
- 注：网络上各种资料质量参差不齐，在其他教程中时常会见到向量对矩阵求导的表达式。例如介绍 RNN 的梯度消失问题的文章中，经常会见到 $\dfrac{\partial l}{\partial W} = \dfrac{\partial l}{\partial \boldsymbol{h}_T} \dfrac{\partial \boldsymbol{h}_T}{\partial \boldsymbol{h}_{T-1}} \cdots \dfrac{\partial \boldsymbol{h}_{i+1}}{\partial \boldsymbol{h}_i} \dfrac{\partial \boldsymbol{h}_i}{\partial W}$ 这种式子。如果文中出现这个式子是定性的，只是为了说明链式法则中出现了很多连乘项导致了梯度消失，那么读者也只需定性地理解即可。如果文中出现这个式子是定量的，是为了推导反向传播的公式，那么笔者建议读者用如下两种方式之一理解：
  - 其一是把 $\dfrac{\partial \boldsymbol{h}_i}{\partial W}$ 理解成一种简写形式：先把 $W$ 抻成一个向量，然后公式中的每一个雅克比矩阵就都可以计算了，最后再把结果向量重新整理成 $W$ 的同型矩阵。但是这种方法非常复杂，因为把 $W$ 抻成向量以后目标函数关于 $W$ 的表达式就变了，很难推导 $\dfrac{\partial \boldsymbol{h}_i}{\partial W}$ 这个雅克比矩阵。一个具体的算例见 [Optimizing RNN performance](https://svail.github.io/rnn_perf/) 一文中最后的推导
    - 如果你不打算熟练掌握这种方法，只浏览一下看看大意即可。相信我，如果你学了本文中的方法，你不会再想用这种把矩阵抻开的方法求导的
  - 其二是把最后一项分母中的 $W$ 理解成矩阵 $W$ 中的任一个元素 $w_{ij}$，从而上述表达式中的每一项都有定义，从而该表达式可以顺利计算。但是这也很麻烦，因为得到的结果不是直接关于 $W$ 的表达式，而是关于它的分量的，最后还要合并起来
  - 其他理解方式，基本上都是作者自己就没弄懂瞎糊弄读者的



#### 实值函数对向量求导

- 未作特殊说明即为对变量 $\boldsymbol{x}$ 求导

- 一个基本的雅克比矩阵（由定义易得）：

  - $\nabla_\boldsymbol{x}(A\boldsymbol{x})=A$
  - 特别地，$\nabla_{\boldsymbol{x}} \boldsymbol{x} = \nabla_{\boldsymbol{x}} (I\boldsymbol{x}) = I $

- 向量内积的求导法则

  - 注：内积是一个实数，因此本节相当于实数对向量求导，结果是与自变量同型的向量。

  - $\nabla(\boldsymbol{a}^T\boldsymbol{x}) = \nabla(\boldsymbol{x}^T\boldsymbol{a}) = \boldsymbol{a}$

    - 证明：$\dfrac{\partial\boldsymbol{a^Tx}}{\partial x_i} = \dfrac{\partial\sum_j a_j x_j}{\partial x_i} = \dfrac{\partial a_i x_i}{\partial x_i} = a_i$

  - $\nabla ||\boldsymbol{x}||_2^2 = \nabla(\boldsymbol{x}^T\boldsymbol{x}) = 2\boldsymbol{x}$

    - 证明一（直接计算）：$\dfrac{\partial ||\boldsymbol{x}||_2^2}{\partial x_i} = \dfrac{\partial\sum_j x_j^2}{\partial x_i} = \dfrac{\partial x_i^2}{\partial x_i} = 2x_i$
    - 证明二（变量多次出现的求导法则）：$\nabla(\boldsymbol{x}^T\boldsymbol{x}) = \nabla_{\boldsymbol{x}}(\boldsymbol{x}_c^T\boldsymbol{x}) + \nabla_{\boldsymbol{x}}(\boldsymbol{x}^T\boldsymbol{x}_c) = 2\nabla_{\boldsymbol{x}}(\boldsymbol{x}_c^T\boldsymbol{x}) = 2\boldsymbol{x}_c = 2\boldsymbol{x}$，其中 $\boldsymbol{x}_c$ 表示将 $\boldsymbol{x}$ 的此次出现不视作自变量，而是视作与 $\boldsymbol{x}$ 无关的常数，下同。

  - $\nabla (\boldsymbol{x}^TA\boldsymbol{x}) = (A+A^T)\boldsymbol{x}$

    - 证明（变量多次出现的求导法则）：$$\begin{align*} 
    LHS & = & \nabla (\boldsymbol{x}_c^TA\boldsymbol{x}) + \nabla (\boldsymbol{x}^TA\boldsymbol{x}_c) \\
     & = & \nabla ((A^T\boldsymbol{x}_c)^T\boldsymbol{x}) + \nabla ((A\boldsymbol{x}_c)^T\boldsymbol{x}) \\ 
    & = & A^T\boldsymbol{x}_c + A\boldsymbol{x}_c \\
     & = & RHS 
    \end{align*}$$
    - 若 $A$ 是对称矩阵，即 $A=A^T$，上式右边还可以进一步化简为 $2A\boldsymbol{x}$

  - **向量函数内积的求导法则**

    - 若 $\boldsymbol{u}(\boldsymbol{x}):\mathbb{R}^n \rightarrow \mathbb{R}^m, \boldsymbol{v}(\boldsymbol{x}):\mathbb{R}^n \rightarrow \mathbb{R}^m$，则 $\nabla(\boldsymbol{u}^T\boldsymbol{v}) = (\nabla_{\boldsymbol{x}} \boldsymbol{u})^T \boldsymbol{v} + (\nabla_{\boldsymbol{x}} \boldsymbol{v})^T \boldsymbol{u}$

    - 证明（变量多次出现的求导法则 + 一次复合的求导法则）：$LHS=\nabla(\boldsymbol{u}^T\boldsymbol{v}_c)+\nabla(\boldsymbol{u}_c^T\boldsymbol{v}) = (\nabla_{\boldsymbol{x}} \boldsymbol{u})^T \boldsymbol{v}_c + (\nabla_{\boldsymbol{x}} \boldsymbol{v})^T \boldsymbol{u}_c = RHS$


#### 向量数乘求导公式

- $\nabla_{\boldsymbol{x}} (\alpha(\boldsymbol{x})\boldsymbol{f(x)}) = \boldsymbol{f(x)} \nabla_{\boldsymbol{x}^T} \alpha(\boldsymbol{x}) + \alpha(\boldsymbol{x})\nabla_{\boldsymbol{x}}\boldsymbol{f(x)}$

  - 说明：向量对向量求导，结果是一个雅克比矩阵，形状为 $\boldsymbol{f}$ 的维度乘 $\boldsymbol{x}$ 的维度

  - 推导：$\dfrac{\partial \alpha f_i}{\partial x_j} = f_i \dfrac{\partial \alpha}{\partial x_j} + \alpha \dfrac{\partial f_i}{\partial x_j} $，两边逐分量对比一下便知等式成立。

  - 记忆：按两个标量函数相乘的求导法则记，再注意一下**维度相容原理**即可。另外注意，等式左边 $\alpha(\boldsymbol{x})\boldsymbol{f(x)}$ 是向量的数乘（若 $\boldsymbol{f(x)}$ 为行向量也可视作矩阵乘法）；右边 $\alpha(\boldsymbol{x})\nabla_{\boldsymbol{x}}\boldsymbol{f(x)}$ 是矩阵的数乘。


#### 矩阵迹求导

- 未作特殊说明求导变量即为 $X$。由于迹是一个实数，所以相当于实数对矩阵求导，结果是和 $X$ 同型的矩阵。
- 先回顾一下迹的基本性质：
  - 线性性质：$tr(\sum_i c_iA_i) = \sum_ic_i tr(A_i)$
  - 转置不变性：$tr(A) = tr(A^T)$
  - 轮换不变性：$$\begin{align*}
    tr(A_1A_2\cdots A_n) & = &  tr(A_2A_3\cdots A_nA_1) \\
     & = & \cdots \\
    & = & tr(A_{n-1}A_nA_1\cdots A_{n-2}) \\
    & = & tr(A_nA_1\cdots A_{n-2}A_{n-1})
    \end{align*}$$
    - 特别地，$tr(AB) = tr(BA)$
    - **注意，轮换不变性不等于交换性。**例如：$tr(ABC) = tr(BCA) = tr(CAB)$，但是一般情况下 $tr(ABC) \neq tr(ACB)$。
- 基本公式：
  - $\nabla tr(A^TX) = \nabla tr(AX^T) = A$
  - 证明：这其实就是矩阵导数的另一种定义。也可以用逐分量求导验证。
  - 根据此式容易得到另一个式子：$\nabla tr(AX) = \nabla tr(XA) = A^T$
- **迹方法的核心公式**：
  - $\nabla tr(XAX^TB) = B^TXA^T + BXA$
  - 推导（变量多次出现的求导法则。其中 $X_c$ 表示将 $X$ 的此次出现视作常数）：$$\begin{align*}
   LHS & = & \nabla tr(XAX_c^TB) + \nabla tr(X_cAX^TB) \\
    & = & (AX_c^TB)^T + \nabla tr(BX_cAX^T) \\
     & = & B^TX_cA^T + BX_cA = RHS
     \end{align*}$$
  - 这个公式非常重要，在推导最小二乘解等多个问题上都会遇到。公式的名字是我瞎起的。
- 其他与矩阵迹有关的公式
  - 大部分都是上述核心公式的简单推论，不必强记，用的时候顺手推就行
  - $\nabla\boldsymbol{a}^TX\boldsymbol{b} = \boldsymbol{ab}^T$
    - 推导：$LHS = \nabla tr(\boldsymbol{a}^TX\boldsymbol{b}) = \nabla tr(X\boldsymbol{ba}^T) = \boldsymbol{ab}^T = RHS$
    - 注：将实数看作是 1*1 矩阵的迹是很常用的技巧。
  - $\nabla\boldsymbol{a}^TX^TX\boldsymbol{a} = 2X\boldsymbol{aa}^T$
    - 推导：$LHS = \nabla tr(\boldsymbol{a}^TX^TX\boldsymbol{a}) = \nabla tr(X\boldsymbol{a}\boldsymbol{a}^TX^T) = \nabla tr(X\boldsymbol{a}\boldsymbol{a}^TX^TI)$，然后套迹方法的核心公式
  - $\nabla (X\boldsymbol{a}-\boldsymbol{b})^T(X\boldsymbol{a}-\boldsymbol{b}) = 2(X\boldsymbol{a}-\boldsymbol{b})\boldsymbol{a}^T$
    - 推导：将左式的括号相乘展开，然后用前几个公式计算结果并化简
  - $\nabla||XA^T-B||_F^2 = 2(XA^T-B)A$
    - 推导同上，只需注意到 $||A||_F^2 = tr(A^TA)$ 即可。特别地，$\nabla ||X||^2_F = \nabla (X^TX) = 2X$（此式也可逐元素求导直接验证）



#### 矩阵求导的链式法则

- 设 $y = f(U), U = G(X)$，则：
  - $\dfrac{\partial y}{\partial{x_{ij}}} = \sum_{k,l} \dfrac{\partial y}{\partial{u_{kl}}} \dfrac{\partial{u_{kl}}}{\partial{x_{ij}}}$，或简写为$\dfrac{\partial{y}}{\partial{x_{ij}}} = tr((\dfrac{\partial{y}}{\partial{U}})^T \dfrac{\partial{U}}{\partial{x_{ij}}})$
  - 关于维度的说明：$X$ 是矩阵，中间变量 $U$ 也是矩阵（未必与 $X$ 同型），最终结果 $y$ 是实数。因此求导结果是和 $X$ 同型的矩阵。
  - 注：此式似乎用的不多，毕竟这仅仅是对 $x_{ij}$ 这一个分量求导的结果，很难直接得到对 $X$ 求导的结果。而且这个式子只是最基础的多元函数复合的链式法则而已，没有得到什么特别有趣或者重要的结论。
- 设 $y = f(u), u = g(X)$，则：$\dfrac{\partial y}{\partial X} = \dfrac{\partial y}{\partial u} \dfrac{\partial u}{\partial X}$ （等式右边是实数和矩阵的数乘）
  - 关于维度的说明：$X, u, y$ 分别是矩阵、实数、实数，因此相当于实数对矩阵求导，结果是与 $X$ 同型的矩阵。
  - 证明是显然的，逐元素求导验证即可：$\dfrac{\partial y}{\partial{x_{ij}}} = \dfrac{\partial y}{\partial u} \dfrac{\partial u}{\partial{x_{ij}}}$。
- **线性变换的导数**：
  - 设有 $f(Y):\mathbb{R}^{m\times p}\rightarrow\mathbb{R}$ 及线性映射 $X\mapsto Y=AX+B:\mathbb{R}^{n\times p}\rightarrow\mathbb{R}^{m\times p}$（因此 $A \in \mathbb{R}^{m\times n}, B \in \mathbb{R}^{m\times p}$），则：
    - $\nabla_{X} \;f(AX+B) = A^T \nabla_Y f$
    - 推导：$\dfrac{\partial f}{\partial x_{ij}} = \sum_{k,l} \dfrac{\partial f}{\partial y_{kl}} \dfrac{\partial y_{kl}}{\partial x_{ij}}$，而 $ \dfrac{\partial y_{kl}}{\partial x_{ij}} = \dfrac{\partial \sum_s a_{ks}x_{sl}}{\partial x_{ij}} = \dfrac{\partial a_{ki}x_{il}}{\partial x_{ij}} = a_{ki}\delta_{lj}$（$\delta_{lj}$ 是 Kronecker $\delta$ 符号，两个角标相等时为1，否则为0），将后式代入前式，得：$\dfrac{\partial f}{\partial x_{ij}} = \sum_{k,l} \dfrac{\partial f}{\partial y_{kl}} a_{ki}\delta_{lj} = \sum_{k} \dfrac{\partial f}{\partial y_{kj}} a_{ki}$，即矩阵 $A^T$ 的第 $i$ 行 和矩阵 $\nabla_Y f$ 的第 $j$ 列的内积。
  - 记忆方法：先做线性变换再求导就等于先求导再做线性变换。剩下的细节（如左乘还是右乘等）根据维度相容原则倒腾即可
  - 向量的线性变换是矩阵线性变化的退化情形，即：
    - 若 $\boldsymbol{y}\overset{\mathrm{def}}{=}A\boldsymbol{x+b}$，则 $\nabla_{\boldsymbol{x}} \;f(A\boldsymbol{x}+\boldsymbol{b}) = A^T \nabla_\boldsymbol{y} f$
    - 向量的线性变换还可以求二阶导：$\nabla^2_{\boldsymbol{x}} \;f(A\boldsymbol{x+b}) = A^T (\nabla^2_\boldsymbol{y} f) A$
    - 推导：记 $\boldsymbol{u(y)} = \nabla_\boldsymbol{y} f, \boldsymbol{w(u)} = A^T \boldsymbol{u} = A^T \nabla_\boldsymbol{y} f$，则 $LHS = \nabla_{\boldsymbol{x}} (\nabla_{\boldsymbol{x}} \;f(A\boldsymbol{x}+\boldsymbol{b})) = \nabla_\boldsymbol{x} \boldsymbol{w} = \dfrac{\partial \boldsymbol{w}}{\partial \boldsymbol{u}} \dfrac{\partial \boldsymbol{u}}{\partial \boldsymbol{y}} \dfrac{\partial \boldsymbol{y}}{\partial \boldsymbol{x}}= A^T (\nabla^2_\boldsymbol{y} f) A$
  - 由于线性变换很常用，这里不妨把给 $X$ 右乘一个矩阵时的公式一并给出，以便查阅
    - 设有$f(Y):\mathbb{R}^{m\times p}\rightarrow\mathbb{R}$及线性映射 $X\mapsto Y=XC+D:\mathbb{R}^{m\times n}\rightarrow\mathbb{R}^{m\times p}$（因此 $C \in \mathbb{R}^{n\times p}, D \in \mathbb{R}^{m\times p}$），则：$\nabla_{X} \;f(XC+D) = (\nabla_{Y} f) C^T$
    - 证明：将 $X^T$ 和 $Y^T$ 分别视为自变量和中间变量，则：$X^T \rightarrow Y^T=C^TX^T + D^T \rightarrow f$。于是 $\nabla_{X} f = (\nabla_{X^T}f)^T = (C \nabla_{Y^T} f)^T = (\nabla_{Y^T} f)^T C^T = (\nabla_{Y} f) C^T$
  - 注：在多层感知机神经网络中，经常有形如 $W \rightarrow \boldsymbol{z} = W\boldsymbol{x} + \boldsymbol{b} \rightarrow l$ 的依赖关系。其中 $\boldsymbol{x}$ 是神经网络某一层的输入，$W, \boldsymbol{b}$ 是该层的参数，$\boldsymbol{z}$ 是经过变换后预备输入给下一层的值，$l$ 是最终的损失函数。根据上述线性变换的求导公式，立即可以得到 BP 算法的核心步骤：$ \nabla_W l = \nabla_\boldsymbol{z} l \; \boldsymbol{x}^T$ 。
    - 另：标准的 BP 算法通常将 $\nabla_\boldsymbol{z} l$ 定义为变量 $\delta$



#### 行列式和逆矩阵求导

- 这一部分在机器学习中遇到的不多（毕竟常见的情况是求一个标量损失函数对其他变量的导数），不是特别重要，不过偶尔在凸优化里会碰到一些。这里收集整理这几个式子主要是为了资料完整、查阅方便。以下假定 $F, X$ 是可逆方阵。
- 行列式的求导公式（ [Jacobi's Fomula](https://en.wikipedia.org/wiki/Jacobi%27s_formula)）：
  - $(|F|)'_x = tr(adj(F)F'_x)$
    - 实数对实数求导，结果也是实数
    - 其中 $adj(F)=|F|F^{-1}$ 是 $F$ 的伴随矩阵，因此有时此式也写作 $(|F|)'_x =|F| tr(F^{-1}F'_x)$
    - 这一条证明起来比较难，大致过程是用逐元素求导 + 伴随矩阵的性质推导，可以参考相应的维基页面
  - 两种特殊情形
    - 取 $x=f_{ij}$ 即得：$(|F|)'_{f_{ij}} = [adj(F)^T ]_{ij}$
    - 将上式的结果组装成一个矩阵，得：$\nabla_F |F| = adj(F)^{-1}=|F|(F^{-1})^T$
      - 左边是实数对矩阵求导，结果为和 $F$ 同型的矩阵
- $(\ln |F|)'_x = tr(F^{-1}F'_x)$
  - 自变量和函数值都是实数，求导结果也是实数
  - 推导：根据最基本的一元函数复合的求导法则即可。令 $u = |F|, y = \ln u$，则：$y'_x = y'_u u'_x = \dfrac{1}{u} (|F| tr(F^{-1}F'_x)) = tr(F^{-1}F'_x)$
- $(F^{-1})'_x = -F^{-1} F'_x F^{-1}$
  - 矩阵对实数求导，结果是和 $F^{-1}$ 同型的矩阵（也是和 $F$ 同型的矩阵）
  - 推导：恒等式 $FF^{-1}=I$ 两边同时对 $x$ 求导，得 $F'_xF^{-1} + F(F^{-1})'_x=O$，移项即得 $(F^{-1})'_x=-F^{-1}F'_xF^{-1}$





## 常见技巧及注意事项

- 实数在与一堆矩阵、向量作数乘时可以随意移动位置。
- 实数乘行向量时，向量数乘与矩阵乘法（$1\times 1$ 矩阵和 $1\times m$ 矩阵相乘）的规则是一致的。
- 遇到相同下标求和就联想到矩阵乘法的定义，即$c_{ij} = \sum_j a_{ij}b_{jk}$。特别地，一维下标求和联想到向量内积$\sum_i u_iv_i = \boldsymbol{u}^T\boldsymbol{v}$，二维下标求和联想到迹 $\sum_{ij}a_{ij}b_{ij} = tr(A^TB)$（$A,B$ 应为同型矩阵）。
  - 如果在一个求和式中，待求和项不是实数而是矩阵的乘积，不要想着展开求和式，而要进一步按照上面的思路，看成分块矩阵的相乘！
- 向量的模长平方（或实数的平方和）转化为内积运算：$\sum_i x_i^2 = \boldsymbol{x}^T\boldsymbol{x}$。矩阵的 F 范数的平方转化为迹运算：$||A||^2_F = tr(AA^T)$。
- 多个矩阵相乘时，多用矩阵迹的求导公式转化、循环移动各项。
- 实数可以看成 $1\times 1$ 矩阵的迹！
- 需要用到向量（或矩阵）对矩阵求导的情形，要么把矩阵按列拆开转化成向量对向量求导（本文后面的算例 PRML (3.33) 说明了这种方法怎么用），要么套用线性变换的求导公式（常见于神经网络的反向传播过程）。





## 算例

#### 线性方程组 $A\boldsymbol{x}=\boldsymbol{b}$ 的最小二乘解

- 即求解 $ \text{argmin}_\boldsymbol{x} \frac{1}{2}||A\boldsymbol{x}-\boldsymbol{b}||^2_2$

- 方法一：展开括号，再使用几个常用公式化简即可：

- $$
  \begin{align*}
      \nabla_\boldsymbol{x} \frac{1}{2}||A\boldsymbol{x}-\boldsymbol{b}||^2_2 & = & \frac{1}{2}\nabla_\boldsymbol{x} (A\boldsymbol{x}-\boldsymbol{b})^T(A\boldsymbol{x}-\boldsymbol{b}) \\
        & = & \frac{1}{2}\nabla_\boldsymbol{x}(\boldsymbol{x}^TA^TA\boldsymbol{x} - \boldsymbol{b}^TA\boldsymbol{x} - \boldsymbol{x}^TA^T\boldsymbol{b} + \boldsymbol{b}^T\boldsymbol{b}) \\
        & = & \frac{1}{2}\left(\nabla_\boldsymbol{x}(\boldsymbol{x}^TA^TA\boldsymbol{x}) - 2\nabla_\boldsymbol{x}(\boldsymbol{b}^TA\boldsymbol{x}) + \nabla_\boldsymbol{x}(\boldsymbol{b}^T\boldsymbol{b})  \right)\\
        & = & A^TA\boldsymbol{x} - A^T\boldsymbol{b} + \boldsymbol{0} \\
        & = & A^T(A\boldsymbol{x}-\boldsymbol{b})
  \end{align*}
  $$

- 方法二：使用线性变换的求导公式 ：

- $$
  \begin{align*}
  \nabla_\boldsymbol{x} \frac{1}{2}||A\boldsymbol{x}-\boldsymbol{b}||^2_2 & = & \frac{1}{2}A^T\nabla_{A\boldsymbol{x}-\boldsymbol{b}} ||A\boldsymbol{x}-\boldsymbol{b}||^2_2 \\
   & = & \frac{1}{2}A^T(2(A\boldsymbol{x}-\boldsymbol{b})) \\
   & = & A^T(A\boldsymbol{x}-\boldsymbol{b})
  \end{align*}
  $$

- 令导数等于零，再给方程两边同时左乘 $(A^TA)^{-1}$，移项即得：$\boldsymbol{x}=(A^TA)^{-1}A^T\boldsymbol{b}$

  - 这里假定方程组是超定的，即 $A$ 列满秩且行数大于列数，因此上述逆矩阵存在
  - 补：如果方程组欠定但是是一致的，那么 $\boldsymbol{x^*}=A^\dagger\boldsymbol{b}$ 是方程 $A\boldsymbol{x}=\boldsymbol{b}$ 的二范数最小的解，其中 $A^\dagger$ 是矩阵 $A$ 的 Moore–Penrose 广义逆。



#### F范数的求导公式推导

- 先转化为迹，再裂项，最后通过恰当的轮换，用迹方法的核心公式处理。

$$
\begin{align*}
    \nabla ||XA^T-B||_F^2 & = & \nabla tr((XA^T-B)^T(XA^T-B)) \\
      & = & \nabla tr(AX^TXA^T - B^TXA^T - AX^TB + B^TB) \\
      & = & \nabla tr(AX^TXA^T) - 2tr(AX^TB) + tr(B^TB)\\
      & = & 2tr(XA^TAX^TI) - 2tr(X^TBA) + O \\
      & = & 2(I^TX(A^TA)^T + IX(A^TA))  - 2BA \\
      & = & 2XA^TA - 2BA \\
      & = & 2(XA^T-B)A
\end{align*}
$$



#### PRML (3.33)求导

- 题目：求$f(W) = \ln p(T|X, W, \beta) = \text{const} -\dfrac{\beta}{2} \sum_n  ||\boldsymbol{t}_n - W^T\phi(\boldsymbol{x}_n)||^2_2$ 关于 $W$ 的导数

- 说明：上面的 $\phi(\boldsymbol{x}_n)$ 的结果应当是一个向量，是指对 $\boldsymbol{x}_n$ 的每个分量应用函数 $\phi(\cdot)$

- 方法一：用矩阵的 F 范数推导

- $$
  \begin{align*}
      \nabla f & = & \nabla \left(-\dfrac{\beta}{2} \sum_n  ||\mathbf{t}_n - W^T\phi(\mathbf{x}_n)||^2_2 \right) \\
        & = & -\dfrac{\beta}{2} \nabla  ||T^T - W^T\Phi^T||_F^2 \\
        & = & -\dfrac{\beta}{2} \nabla  ||T - \Phi W||_F^2 \\
        & = & -\dfrac{\beta}{2} \nabla  ||\Phi W - T||_F^2 \\
        & = & -\dfrac{\beta}{2} \Phi^T (2(\Phi W - T)) \\
        & = & -\beta\Phi^T (\Phi W - T)
       \end{align*}
  $$

  - 上述几步的依据分别是：
    - 将若干个列向量拼成一个矩阵，因此它们的二范数平方和就等于大矩阵的 F 范数的平方
    - 矩阵转置不改变其 F 范数
    - 矩阵数乘 -1 不改变其 F 范数
    - 线性变换的求导公式 + F 范数的求导公式
    - 实数在和矩阵作数乘时位置可以任意移动
  - 有了导数，再另导数等于零，即得 $W$ 的最大似然解：$W_{ML} = \Phi^\dagger T = (\Phi^T\Phi)^{-1}\Phi^TT$

- 方法二： 将向量二范数的平方用内积代替，然后逐项展开，最后利用分块矩阵相乘消掉求和号

- $$
  \begin{align*}
      \nabla f & = & \nabla \left(-\dfrac{\beta}{2} \sum_n  ||\boldsymbol{t}_n - W^T\phi(\boldsymbol{x}_n)||^2_2 \right) \\
        & = & -\dfrac{\beta}{2}\nabla \left(\sum_n (\boldsymbol{t}_n - W^T\phi(\boldsymbol{x}_n))^T(\boldsymbol{t}_n - W^T\phi(\boldsymbol{x}_n)) \right) \\
        & = & -\dfrac{\beta}{2}\sum_n \left\{\nabla(\boldsymbol{t}_n^T\boldsymbol{t}_n) -2\nabla(\phi(\boldsymbol{x}_n)^TW\boldsymbol{t}_n) + \nabla(\phi(\boldsymbol{x}_n)^TWW^T\phi(\boldsymbol{x}_n))\right\} \\
        & = & -\dfrac{\beta}{2}\sum_n \left\{O - 2\phi(\boldsymbol{x}_n)\boldsymbol{t}_n^T + \nabla(WIW^T\phi(\boldsymbol{x}_n)\phi(\boldsymbol{x}_n)^T)\right\}\\
        & = & -\dfrac{\beta}{2}\sum_n \left\{- 2\phi(\boldsymbol{x}_n)\boldsymbol{t}_n^T + (\phi(\boldsymbol{x}_n)\phi(\boldsymbol{x}_n)^T)^T W I^T + (\phi(\boldsymbol{x}_n)\phi(\boldsymbol{x}_n)^T) W I\right\} \\
        & = & -\dfrac{\beta}{2}\sum_n \left\{- 2\phi(\boldsymbol{x}_n)\boldsymbol{t}_n^T + 2\phi(\boldsymbol{x}_n)\phi(\boldsymbol{x}_n)^TWI\right\} \\
        & = & -\beta\sum_n \left\{-\phi(\boldsymbol{x}_n)\boldsymbol{t}_n^T + \phi(\boldsymbol{x}_n)\phi(\boldsymbol{x}_n)^TW\right\} \\
        & = & -\beta\sum_n \boldsymbol{\phi(\boldsymbol{x}_n)}\left\{-\boldsymbol{t}_n^T + \phi(\boldsymbol{x}_n)^TW\right\} \\
        & = & -\beta\Phi^T (\Phi W - T)
       \end{align*}
  $$

  - 这种方法虽然比较繁琐，但是更具有一般性

  - 最后一步化简的思考过程是把对 $n$ 求和视为两个分块矩阵的乘积：

    - 第一个分块矩阵共 $1\times N$ 个块，且第 $n$ 个分量是 $\phi(\boldsymbol{x}_n)$。因此第一个矩阵是 $(\phi(\boldsymbol{x}_1), \phi(\boldsymbol{x}_2), \cdots, \phi(\boldsymbol{x}_n)) = \boldsymbol{\Phi^T}$

    - 第二个分块矩阵共 $N\times 1$ 个块，且第 $n$ 个分量是 $-\boldsymbol{t}_n^T + \phi(\boldsymbol{x}_n)^TW$。因此，第二个矩阵是：

    - $$
      \begin{align*} \\
                          \left(
                          \begin{matrix}
                          -\boldsymbol{t}_1^T + \phi(\boldsymbol{x}_1)^TW \\
                              -\boldsymbol{t}_2^T + \phi(\boldsymbol{x}_2)^TW \\
                              \vdots \\
                              -\boldsymbol{t}_N^T + \phi(\boldsymbol{x}_n)^TW
                          \end{matrix}
                          \right)
                          & = & \left(
                          \begin{matrix}
                          \phi(\boldsymbol{x}_1)^TW \\
                              \phi(\boldsymbol{x}_2)^TW \\
                              \vdots \\
                              \phi(\boldsymbol{x}_n)^TW
                          \end{matrix}
                          \right)
                          -\left(
                          \begin{matrix}
                          \boldsymbol{t}_1^T \\
                              \boldsymbol{t}_2^T \\
                              \vdots \\
                              \boldsymbol{t}_N^T
                          \end{matrix}
                          \right) \\
                          & = & \left(
                          \begin{matrix}
                          \phi(\boldsymbol{x}_1)^T \\
                              \phi(\boldsymbol{x}_2)^T \\
                              \vdots \\
                              \phi(\boldsymbol{x}_n)^T
                          \end{matrix}
                          \right)W
                          -\left(
                          \begin{matrix}
                          \boldsymbol{t}_1^T \\
                              \boldsymbol{t}_2^T \\
                              \vdots \\
                              \boldsymbol{t}_N^T
                          \end{matrix}
                          \right) \\
                          & = & \Phi W - T
                      \end{align*}
      $$

      - 注意上述第二个等号的推导过程也是一个分块矩阵乘法：前一项是两个分块矩阵的乘积，两个分块矩阵分别由 $N\times 1$ 和 $1\times 1$ 个块组成


#### 学习仿射变换

- 假设有 $m$ 对样本点 $(\boldsymbol{x}_i, \boldsymbol{y}_i)$，需要学习一个仿射变换 $\boldsymbol{y} =A\boldsymbol{x}+\boldsymbol{b}$，使得变换后整个数据集上的拟合误差最小（这里不需要 $\boldsymbol{x}$ 和 $\boldsymbol{y}$ 维度相同）。即求解 $\text{argmin}_{A, \boldsymbol{b}} f(A, \boldsymbol{b}) = \dfrac{1}{2m} \sum_i||A\boldsymbol{x}_i + \boldsymbol{b} - \boldsymbol{y}_i||^2_2$

  - 该问题的实际应用例如：用两种语言的单语语料各自训练了一份词向量，现在已知两种语言的一些词对互为翻译，希望将两种语言的词向量空间对齐。

- 和前两道题目类似，本题唯一的不同之处是多了一个偏置项 $\boldsymbol{b}$。同理，本题也有两种做法，一种是把范数符号内的每个向量凑成大矩阵统一求；另一种是直接带着求和号求导，最后用分块矩阵乘法的观点把结果整合成矩阵形式。

- 这里主要想讲的是**如何处理“复制”的问题**

  - 例如，在神经网络中，如果要对一个 batch 一起计算，需要在中间的隐层里把相同的偏置项加到 batch 里每个样本的隐层状态上；再比如在计算 Batch Norm 时，要给每个样本都减去当前 batch 的均值。
  - **解决办法就是乘全 1 向量！**
    - 用一个长为 $m$ 的全 1 行向量右乘 $\boldsymbol{b}$，就相当于把它复制 $m$ 份拼在一起
    - 有时会看到给输入 $\boldsymbol{x}$ 加一维常数特征 1，其实就等价于这里的偏置项右乘全 1 向量的操作
    - 这个技巧不妨直接记住，就不用每次都用分块矩阵慢慢凑了

- 记

- $$
  X = 
  \left[ \begin{array}{cccc}
  | & | &  & |  \\
  \boldsymbol{x}_1 & \boldsymbol{x}_2 & \cdots  & \boldsymbol{x}_m  \\
  | & | &  & |  \\
  \end{array}
  \right],
  
  Y = 
  \left[ \begin{array}{cccc}
  | & | &  & |  \\
  \boldsymbol{y}_1 & \boldsymbol{y}_2 & \cdots  & \boldsymbol{y}_m  \\
  | & | &  & |  \\
  \end{array}
  \right]
  $$

  - 即每行对应一个特征，每列对应一个样本
  - 则 $f=\dfrac{1}{2m} ||AX+\boldsymbol{b1}_m^T - Y||^2_F$

- 然后求导就很简单了

  - $\nabla_A f=\dfrac{1}{m}(AX+\boldsymbol{b1}_m^T - Y)X^T$
  - $\nabla_\boldsymbol{b} f=\dfrac{1}{m}(AX+\boldsymbol{b1}_m^T - Y)\boldsymbol{1}_m$





#### MLP 的反向传播

- 以经典的 MNIST 手写数字分类问题为例，假设我们使用一个单个隐层的多层感知机来预测当前图像的类别。首先把输入图像拉伸成 $n=784$ 维的向量 $\boldsymbol{x}$，然后通过线性变换使其变成 $p=500$ 的隐层向量 $\boldsymbol{z}^{(1)}$，使用 sigmoid 函数进行激活得到 $\boldsymbol{a}^{(1)}$；再经过一次线性变换变成维度是 $q=10$ 的向量 $\boldsymbol{z}^{(2)}$，最后用 softmax 函数预测每一个数字的概率 $\boldsymbol{a}^{(2)}$，用交叉熵损失函数计算预测结果和真实结果 $\boldsymbol{y}$（one-hot 向量）之间的误差 $l$。

- 写成数学公式即为：

- $$
  \begin{align*}
    l(W^{(1)},W^{(2)},b^{(1)}, b^{(2)}) & = & -\boldsymbol{y}^T \ln \boldsymbol{a}^{(2)} \\
    \boldsymbol{a}^{(2)} & = & g(\boldsymbol{z}^{(2)}) \\ 
    \boldsymbol{z}^{(2)} & = & W^{(2)}\boldsymbol{a}^{(1)} + \boldsymbol{b}^{(2)} \\ 
   \boldsymbol{a}^{(1)} & = & h(\boldsymbol{z}^{(1)}) \\ 
    \boldsymbol{z}^{(1)} & = & W^{(1)}\boldsymbol{x} + \boldsymbol{b}^{(1)}
         \end{align*}
  $$

  - 其中各个变量的维度是：$\boldsymbol{x}\in \mathbb{R}^{n}, \boldsymbol{z}^{(1)}, \boldsymbol{b}^{(1)}, \boldsymbol{a}^{(1)} \in \mathbb{R}^p, \boldsymbol{z}^{(2)},\boldsymbol{b}^{(2)}, \boldsymbol{a}^{(2)}, \boldsymbol{y} \in \mathbb{R}^q, W^{(1)}\in\mathbb{R}^{p\times n}, W^{(2)}\in\mathbb{R}^{q\times p}$
  - 激活函数 $h(\cdot)$ 为 sigmoid 函数，$g(\cdot)$ 为 softmax 函数

- 一层一层往前算：

  - $\dfrac{\partial l}{\partial \boldsymbol{a}^{(2)}} = - \dfrac{\boldsymbol{y}}{\boldsymbol{a}^{(2)}}$，其中分数线表示逐分量相除

    - 此式通过逐元素求导即可得到

  - $\delta^{(2)} \overset{def}{=} \dfrac{\partial l}{\partial \boldsymbol{z}^{(2)}} = \left(\dfrac{\partial \boldsymbol{a}^{(2)}}{\partial \boldsymbol{z}^{(2)}}\right)^T \dfrac{\partial l}{\partial \boldsymbol{a}^{(2)}}$

    - 在 BP 算法中，**通常将损失函数 $l$ 对每一层激活前的值 $\boldsymbol{z}$ 的导数定义为变量 $\delta$**

      - 在 MLP 的语境下，$\delta$ 为向量，与本文其他部分的符号表示略有出入

    - 注意：对于任意一种激活函数和损失函数的搭配，只要它们是分片可导的，就能按照这里的流程反向传播，计算出网络里每个参数的导数。但是如果损失函数和激活函数的搭配选得好，反向传播的求导公式形式就会非常简洁。例如本例中**使用 softmax 激活 + 多类交叉熵损失函数，经过化简后最后一层的 $\delta$ 变量形如“模型预测值 - 真值”**。这个结论最好直接记住。这种搭配在广义线性模型（Generalized Linear Model）里被称作 **canonical link function**，详见 PRML 4.3.6 节或其他经典统计学/机器学习教材。正是因为 canonical link function 的存在，有些 BP 算法的流程里会直接写最后一层的 $\delta=o_t - y_t$（模型输出值减真值），然后往前传播。就本例而言，这个结果的推导过程如下：

    - 令 $\boldsymbol{u}=\exp(\boldsymbol z^{(2)})$（逐元素求指数），则 $\boldsymbol a^{(2)} = \text{softmax}(\boldsymbol{z^{(2)}})= \dfrac{1}{\sum\boldsymbol{u}}\boldsymbol{u}$，其中 $\sum{\boldsymbol{u}}$ 表示对 $\boldsymbol{u}$ 的各个分量求和，结果是一个标量。于是可以用向量数乘的求导公式计算 $\dfrac{\partial \boldsymbol a^{(2)}}{\partial \boldsymbol{u}}$：

    - $$
      \begin{split}
      \dfrac{\partial \boldsymbol a^{(2)}}{\partial \boldsymbol{u}} & = \boldsymbol{u} \dfrac{\partial \left(1/\sum\boldsymbol{u}\right)}{\partial \boldsymbol{u}^T} + \dfrac{1}{\sum\boldsymbol{u}}\dfrac{\partial \boldsymbol{u}}{\partial \boldsymbol{u}}\\ 
      & =\boldsymbol{u} \cdot-\dfrac{1}{\left(\sum\boldsymbol{u}\right)^2}\boldsymbol{1}^T + \dfrac{1}{\sum\boldsymbol{u}} I \\
      & = -\dfrac{1}{\left(\sum\boldsymbol{u}\right)^2} \boldsymbol{u}\boldsymbol{1}^T + \dfrac{1}{\sum\boldsymbol{u}} I 
      \end{split}
      $$

      - 其中 $\boldsymbol{1}$ 是和 $\boldsymbol{u}$ 同型的全 1 向量，$I$ 是 $q\times q$ 的单位阵

    - 易见 $\dfrac{\partial \boldsymbol u}{\partial \boldsymbol z^{(2)}} = \text{diag}(\exp{(\boldsymbol{z^{(2)}})}) = \text{diag}(\boldsymbol{u})$

      - $\text{diag}(\cdot)$ 表示将括号里的向量变成一个对角矩阵，跟之前提到的 $\text{vec}(\cdot)$ 互为逆运算

    -  于是可得 **softmax 函数的雅克比矩阵**为: 

    - $$
      \begin{split}
      \dfrac{\partial \boldsymbol{a}^{(2)}}{\partial \boldsymbol{z}^{(2)}} 
      & = \dfrac{\partial \boldsymbol{a}^{(2)}}{\partial \boldsymbol{u}} \dfrac{\partial \boldsymbol{u}}{\partial \boldsymbol{z}^{(2)}} \\
      & = \left[ -\dfrac{1}{\left(\sum\boldsymbol{u}\right)^2} \boldsymbol{u}\boldsymbol{1}^T + \dfrac{1}{\sum\boldsymbol{u}} I \right] \text{diag}(\boldsymbol{u}) \\
      & = -\dfrac{1}{\left(\sum\boldsymbol{u}\right)^2} \boldsymbol{u}\boldsymbol{u}^T + \dfrac{1}{\sum\boldsymbol{u}} \text{diag}(\boldsymbol{u})  \\
      & = -\dfrac{\boldsymbol{u}}{\sum\boldsymbol{u}} \left(\dfrac{\boldsymbol{u}}{\sum\boldsymbol{u}}\right)^T + \dfrac{1}{\sum\boldsymbol{u}} \text{diag}(\boldsymbol{u}) \\
      & = -\boldsymbol{a}^{(2)} {\boldsymbol{a}^{(2)}}^T + \text{diag}(\boldsymbol{a}^{(2)})
      \end{split}
      $$

    - 所以 

    - $$
      \begin{split}
      \delta^{(2)} 
      & = \left(\dfrac{\partial \boldsymbol{a}^{(2)}}{\partial \boldsymbol{z}^{(2)}}\right)^T \dfrac{\partial l}{\partial \boldsymbol{a}^{(2)}} \\
      & = \left[ -\boldsymbol{a}^{(2)} {\boldsymbol{a}^{(2)}}^T + \text{diag}(\boldsymbol{a}^{(2)})\right]^T \left(- \dfrac{\boldsymbol{y}}{\boldsymbol{a}^{(2)}}\right) \\
      & = -\boldsymbol{a}^{(2)} {\boldsymbol{a}^{(2)}}^T \cdot \left(-\dfrac{\boldsymbol{y}}{\boldsymbol{a}^{(2)}}\right) + \text{diag}(\boldsymbol{a}^{(2)}) \cdot \left(-\dfrac{\boldsymbol{y}}{\boldsymbol{a}^{(2)}}\right) \\
      & = \boldsymbol{a}^{(2)} \sum \boldsymbol{y} - \boldsymbol{y} \\
      & = \boldsymbol{a}^{(2)} - \boldsymbol{y}
      \end{split}
      $$

    - 注意上述推导仅用到了 $\sum\boldsymbol{y}=1$ 这一性质，而没有利用 one-hot 分布这一信息。因此该结果对于任意目标概率分布 $\boldsymbol{y}$ 都是成立的。

  - 算出 $\delta^{(2)}$ 之后，剩下的推导就比较按部就班了。使用线性变换的求导公式立即得到：

    - $\dfrac{\partial l}{\partial W^{(2)}} = \delta^{(2)} {\boldsymbol{a}^{(1)}}^T$
    - $\dfrac{\partial l}{\partial \boldsymbol{b}^{(2)}} = \delta^{(2)}$
    - $\dfrac{\partial l}{\partial \boldsymbol{a}^{(1)}} = {W^{(2)}}^T \delta^{(2)}$

  - 再往前推一层：

    - $\delta^{(1)} = \dfrac{\partial l}{\partial \boldsymbol{z}^{(1)}} = \dfrac{\partial l}{\partial \boldsymbol{a}^{(1)}}\odot h'(\boldsymbol{z}^{(1)})$
      - 此式对任意激活函数都成立
      - 若激活函数 $h(\cdot)$ 为 sigmoid 函数，则其导数为 $h'(t)=h(t)(1-h(t))$，于是 $\delta^{(1)} = \dfrac{\partial l}{\partial \boldsymbol{a}^{(1)}}\odot h(\boldsymbol{z}^{(1)}) \odot (\boldsymbol{1}-h(\boldsymbol{z}^{(1)}))$
      - 事实上 sigmoid 函数也是 softmax 函数的特例：由 $\sigma(t) = 1/(1+\exp(-t))$ 变形可得，$\sigma(t) = \exp(t)/(\exp(t)+1) = \exp(t)/(\exp(t)+\exp(0))$，即 $\sigma(t)$ 相当于对二维向量 $(t, 0)^T$ 做 softmax，然后取第一维的结果。另外也容易验证，$\sigma(\cdot) $ 函数的导数表达式和 softmax 函数的雅克比矩阵的左上角 $(1, 1)$ 元的表达式是相容的。

  - 继续反向传播到第一层的参数：

    - $\dfrac{\partial l}{\partial W^{(1)}} = \delta^{(1)} {\boldsymbol{x}}^T$
    - $\dfrac{\partial l}{\partial \boldsymbol{b}^{(1)}} = \delta^{(1)}$
    - $\dfrac{\partial l}{\partial \boldsymbol{x}} = {W^{(1)}}^T \delta^{(1)}$

- 补：其他常用的 canonical link function 搭配及推导过程

  - 约定用 $z, a, y$ 分别表示神经网络最后一层激活前的值、激活后的值、真值
  - 二分类中使用 sigmoid 激活函数 + 交叉熵损失函数
    - 推导：若 $z \rightarrow a=\sigma(z) \rightarrow l=-(y\ln a + (1-y)\ln(1-a))$，则：$\dfrac{\partial l}{\partial z} = \dfrac{\partial l}{\partial a}\dfrac{\partial a}{\partial z}=\left(\dfrac{1-y}{1-a}-\dfrac{y}{a}\right) \left(a(1-a)\right) = (1-y)a - y(1-a) = a-y$
  - 回归问题里使用恒等激活函数 + 最小二乘损失函数
    - 推导：若 $\boldsymbol{z} \rightarrow \boldsymbol{a}=\boldsymbol{z} \rightarrow l=\dfrac{1}{2}(\boldsymbol{a}-\boldsymbol{y})^T(\boldsymbol{a}-\boldsymbol{y})$，则：$\dfrac{\partial l}{\partial \boldsymbol{z}} = \dfrac{\partial l}{\partial \boldsymbol{a}}=\boldsymbol{a} - \boldsymbol{y}$



#### RNN 的梯度消失/爆炸问题

- 通常 RNN 的状态方程的更新定义为 $\boldsymbol{h}_t = f(W\boldsymbol{h}_{t-1} + U\boldsymbol{x}_t + \boldsymbol{b})$（$f$ 表示一个逐元素的激活函数，例如 $\tanh(\cdot)$ 等），而这里我们采用 Pascanu 等人的论文 [On the difficulty of training Recurrent Neural Networks](https://arxiv.org/abs/1211.5063) 中的定义，即认为 $\boldsymbol{h}_t = Wf(\boldsymbol{h}_{t-1}) + U\boldsymbol{x}_t + \boldsymbol{b}$（这两种方程其实是等价的，只是前一种表述把隐层状态定义成激活后的值，后一种表述把隐层状态定义成激活前的值，前述论文中的脚注里也有说明。这里采用后一种方式，是因为它稍微好算一点）。
- 展开后的网络结构示意图参见 [CS224d-lecture8](https://cs224d.stanford.edu/lectures/CS224d-Lecture8.pdf) 中的 Slide 14，这里截图展示如下：![RNN-unfolded](RNN-unfolded.PNG)
  - 读者可以根据这个 slides 来梳理思路，了解 RNN 做反向传播的大体流程（当然也可以直接看本文后面的推导），但是这个 slides 中的计算有错，具体的计算结果慎看，小心把自己搞混！
- 现在我们来计算损失函数 $l$ 对循环连接的权重矩阵 $W$ 的导数：假设每一时间步都有一个误差 $l_t$（例如建立一个语言模型，每一步都要预测下一个词的概率分布，与语料库里的真实值计算交叉熵），总的误差等于每一步的误差加起来：$l = \sum_t l_t$，因此 $\dfrac{\partial l}{\partial W} = \sum_t \dfrac{\partial l_t}{\partial W}$（对一元函数来说，和的导数等于导数的和。根据多元函数偏导数的定义，很容易推广到多元函数上，进而推广到矩阵求导上）。
- 考虑到矩阵 $W$ 出现了多次，计算 $\dfrac{\partial l_t}{\partial W}$ 需要计算 $l_t$ 对 $W$ 的每一次出现的导数，然后再求和。若用 $W^{(k)}$ 表示 $\boldsymbol{h}_{k-1}$ 与 $\boldsymbol{h}_k$ 之间的转移矩阵 $W$，则 $\dfrac{\partial l_t}{\partial W} = \sum_{k=1}^t \dfrac{\partial l_t}{\partial W^{(k)}} = \sum_{k=1}^t \dfrac{\partial l_t}{\partial \boldsymbol{h}_k} (f(\boldsymbol{h}_{k-1}))^T$。其中第二个等号用到的是线性变换的求导公式（类似标准 BP 算法的核心步骤）
- 然后根据雅克比矩阵的运算规则计算损失函数对隐层的导数
  - 先计算 $\dfrac {\partial \boldsymbol{h}_{i+1}}{\partial \boldsymbol{h}_{i}} = \dfrac {\partial \boldsymbol{h}_{i+1}}{\partial f(\boldsymbol{h}_{i})} \dfrac {\partial f(\boldsymbol{h}_{i})}{\partial \boldsymbol{h}_{i}}= W \text{diag}(f'(\boldsymbol{h}_{i})) $
    - Stanford 的讲义和前述论文中，均认为 $\dfrac {\partial \boldsymbol{h}_{i+1}}{\partial \boldsymbol{h}_{i}} = W^T \text{diag}(f'(\boldsymbol{h}_{i}))$，这一点应该是错的，矩阵 $W$ 不应该被转置，根据雅克比矩阵的定义写一个梯度检查的程序即可快速验证这一点。不过这个小错误不影响 RNN 梯度消失/爆炸现象的论证。
  - 根据多次复合的向量求导法则，得： $$\begin{align*} 
  \dfrac{\partial l_t}{\partial \boldsymbol{h}^T_k} & = & \dfrac{\partial l_t}{\partial \boldsymbol{h}^T_t} \dfrac{\partial \boldsymbol{h}_{t}}{\partial \boldsymbol{h}_{t-1}} \cdots \dfrac{\partial \boldsymbol{h}_{k+1}}{\partial \boldsymbol{h}_{k}} \\
   & = & \dfrac{\partial l_t}{\partial \boldsymbol{h}^T_t} W \text{diag}(f'(\boldsymbol{h}_{t-1})) \cdots W \text{diag}(f'(\boldsymbol{h}_{k}))
   \end{align*}$$
  - 将此式两边转置，再代入 $\dfrac{\partial l_t}{\partial W}$ 中，就能得到最终结果。类似地，$\dfrac{\partial l_t}{\partial \boldsymbol{b}} = \dfrac{\partial l_t}{\partial \boldsymbol{h}_t},  \dfrac{\partial l_t}{\partial U} = \dfrac{\partial l_t}{\partial \boldsymbol{h}_t}\boldsymbol{x}_t^T, \dfrac{\partial l_t}{\partial \boldsymbol{x}_t} = U^T\dfrac{\partial l_t}{\partial \boldsymbol{h}_t}$，这就是 vanilla RNN 的 BPTT 的公式。中间很多个隐层之间的雅克比相乘那一部分也可以用求积符号来书写，不过展开写更清楚一些。
- 注：实践中具体计算梯度的时候，一般还是先定义一组类似于 BP 神经网络中的 $\delta_t$ 的变量，使用循环逐层进行计算。这里只是为了展示向量求导的方法，强行把每一步的结果都展开了。



#### Autoencoder with Tied-weight

- 求函数 $f(W, \boldsymbol{b}_1, \boldsymbol{b}_2) = l(\boldsymbol{b}_2 + W^T \sigma(W\boldsymbol{x} + \boldsymbol{b}_1))$ 对 $W$ 的导数，其中 $\sigma(\cdot)$ 是逐元素求 Sigmoid。

- 根据变量多次出现的求导法则计算即可（ $W_c$ 的含义是将 $W$ 此次出现视作常数）：$\nabla_W f = \nabla_W l(\boldsymbol{b}_2 + W^T \sigma(W_c\boldsymbol{x} + \boldsymbol{b}_1)) + \nabla_W l(\boldsymbol{b}_2 + W_c^T \sigma(W\boldsymbol{x} + \boldsymbol{b}_1))$

- 为方便计算，定义如下几个中间变量：

  - $\boldsymbol{u} = W\boldsymbol{x} + \boldsymbol{b}_1, \boldsymbol{v} = \sigma(\boldsymbol{u}), \boldsymbol{t} = \boldsymbol{b}_2 + W_c^T \boldsymbol{v}$

- 上式右边第一项计算如下：

- $$
  \begin{align*}
  \nabla_W \, l(\boldsymbol{b}_2 + W^T \sigma(W_c\boldsymbol{x} + \boldsymbol{b}_1)) & = & \left(\nabla_{W^T} l(\boldsymbol{b}_2 + W^T \sigma(W_c\boldsymbol{x} + \boldsymbol{b}_1))\right)^T \\
  & = & \left(\nabla_{\boldsymbol{t}} l(\boldsymbol{t}) \; \cdot \sigma(W_c\boldsymbol{x} + \boldsymbol{b}_1)^T \right)^T \\
  & = & \sigma(W_c\boldsymbol{x} + \boldsymbol{b}_1) (\nabla_{\boldsymbol{t}} l(\boldsymbol{t}))^T
       \end{align*}
  $$

- 第二项计算如下：

- $$
  \begin{align*}
  \nabla_W \, l(\boldsymbol{b}_2 + W_c^T \sigma(W\boldsymbol{x} + \boldsymbol{b}_1)) & = & \nabla_{\boldsymbol{u}} l(\boldsymbol{b}_2 + W_c^T \sigma(\boldsymbol{u})) \; \boldsymbol{x}^T \\
  & = & (\nabla_{\boldsymbol{u}^T} l(\boldsymbol{b}_2 + W_c^T \sigma(\boldsymbol{u})))^T \; \boldsymbol{x}^T \\
  & = & \left(\nabla_{\boldsymbol{t}^T} l(\boldsymbol{t}) \dfrac{\partial \boldsymbol{t}}{\partial \boldsymbol{v}} \dfrac{\partial \boldsymbol{v}}{\partial \boldsymbol{u}} \right)^T  \boldsymbol{x}^T \\
  & = & \left(\nabla_{\boldsymbol{t}^T} l(\boldsymbol{t})W_c^T 
  \text{diag} (\sigma'(\boldsymbol{u}))\right)^T  \boldsymbol{x}^T \\
  & = & \text{diag}(\sigma'(\boldsymbol{u}))W_c\nabla_{\boldsymbol{t}} l(\boldsymbol{t})  \boldsymbol{x}^T
       \end{align*}
  $$

- 其中第三个等号是多步复合函数求导的公式

- 最终结果就是将以上两项合并起来，并去掉所有 $W_c$ 中的下标，从略。