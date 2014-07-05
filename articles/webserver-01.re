= Webサーバの基本

Android端末を有効活用する上では、インターネット、あるいはクラウド、そしてそこにあるサーバについて理解し、
それらと通信することが欠かせません。

本章から続く３つの章では、Android端末の世界から少し離れ、Webサーバを取り巻く世界を概観し、
Androidアプリにおいても役立つ教訓を得ることを目標とします。

本章ではまず、Webサーバに役に立つ基礎知識を学習・復習します。
次章で、本章で説明する概要を詳細に掘り下げていき、
最後の章では実際にWebサーバを作成する流れを考えていくことにします。

サーバ、という言葉はAndroidアプリの開発でもしばしば登場するものですが、
復習も兼ねてこの言葉についてもう一度考えてみます。

サーバを語る上では「クライアント・サーバモデル」を理解する必要があります。
そしえｔ，クライアントとサーバ間の通信にはやりとりのルール、すなわち「プロトコル」が必要です。

Webサーバは簡単に言えば「Webページを返してくれるサーバ」です。
本章の最後に「Web」とつくサーバとそのプロトコルについて考えます。

== サーバ

Webにおいては、WebブラウザやAndroidアプリからWebサーバへWebページなどを「リクエスト」し、Webサーバが「レスポンス」を返します。
requestは「要求」を意味する英単語で、responseは「返答」の英単語です。

WebサーバがAndroid端末に接続してくるということは通常ありません。
「リクエスト」は常にAndroid端末、アプリが行い、「レスポンス」Webサーバが行います。

より一般的に、データを要求する側をクライアント、返答をする側をサーバと呼びます。
「クライアント・サーバモデル」という、インターネット・クラウドで非常に一般的なモデル（考え方）の一つです。

サーバという言葉は、英語で言えばserverです。
日本語でも、例えば「ジュースサーバ」「ビールサーバ」といった表現で登場します。
@<fn>{server}

//image[juiceserver][ジュースサーバー]{
//}

「ジュースサーバ」は相手にジュースを提供します。
Webサーバは、例えばWebページのようなインターネット・クラウド上にある情報を提供するために存在します。

//footnote[server][英語名詞であるserverに対応する動詞（「〜する」）はserveです。これは「〜に仕える」「〜のために働く」という意味です。serverのコンピュータ関連の用語ではない本来の意味は「給仕人」「接客係」です。ちなみに給仕の読みは「きゅうじ」であって「きゅうし」ではありません。]

WebブラウザやAndroid端末は、Webサーバから見て「クライアント」です。

通常のAndroidアプリを作る限り、「Webサーバから見てAndroid端末やアプリがクライアントである」と考えてしまって構いません。
@<fn>{android_maybe_server}

//footnote[android_maybe_server][Webサーバからちょっと離れて、複数のAndroid端末間でWiFi経由で対戦ゲームを行うケースを考えましょう。このとき、多くのAndroid端末はクライアントですが、どれか一つはサーバになり、その他の端末からの接続を待つのが一般的です。具体的にはまず、サーバ側がゲームを行うための「部屋」を作り、その他の端末の接続を待ちます。その他の端末はしばしば「ホスト」とも呼ばれるそのサーバへクライアントとして接続します。全員が揃った段階で、ゲームを開始します。このとき、サーバもしくは「ホスト」の役割は別の端末が行うこともありえます。このとき、その別の端末が今度はサーバで、さきほどサーバだった端末はクライアントとなります。]

クライアントであるAndroid端末は、
例えばWebブラウザを経由してWebサーバに情報を取りにいきます。
この場合、ざっくりと言えば

 * Android端末はクライアントとしてサーバにデータを取りに行く
 * サーバはクライアントの要求を受け取り、要求に見合ったデータを返す

という作業が発生します。

=== P2P

別のモデル（考え方）にP2P（ピアツーピア, Peer to Peer）というものもあります。

例えば、電話を考えてみます。電話をかける側とうける側という立ち位置で見ると、どちらがどちらに電話をかけても問題はありません。
「クライアント・サーバモデル」のように、どちらかが常に待ち受けている必要はないのです。
インターネット電話アプリのSkypeでもそれは似ていて、
相手と通話する際にはどちらからどちらに繋げる（リクエストを投げる）こともできます。

このモデルでは、データを要求する側と提供する側が柔軟に入れ替わるため、どちらがサーバともクライアントとも言えないような通信の仕方をします。
実際の生活でも、インターネット上でも、必ずしも「サーバ・クライアントモデル」が対話を行う唯一のモデル（考え方）ではない、と理解してもらえれば十分です。
@<fn>{server_exists}

Peerは「同僚」といった意味の英語です。
ServerがClientにServe（仕える）という非対称の関係を明確に意図しているのに対して、Peerは通信相手同士が同格であることが明確になっています。

//footnote[server_exists][実際にはかける相手を特定する必要がありますから、言ってみれば「交換手」に相当するサーバが存在しなければ成り立ちません。]

== プロトコル
=== 一人で開発するアプリの内部構造

相手がいなければ自分でルールを決めてしまうことが出来ます。

「このデータはHogeHogeClassが持つ」といったルールを途中で変えて、
HogeHogeClassを継承したHogePostClassを新たに実装しても、
ユーザに見えない範囲では文句を言われることはあまりありません。
自分がそれを守れば良いのです。

=== 相手がいるからにはルールが必要

しかし「クライアント・サーバモデル」や「P2P」のように相手がいる場合、
世界中に分散しているサーバ、人々と通信します。
「ネットワーク」の章でも学んだ通り、
相手がいる場合には何らかのルール、つまり「プロトコル」(protocol)が必要です。
@<fn>{about_protocol}

//footnote[about_protocol][インターネットに関する技術的な話を除くと、国家間の外交に関するニュース等で「プロトコル」という言葉を散見する印象を筆者は持ちます。その場合は「外交儀礼」という意味で、例えば他国の王族をもてなす際には一定の手順、すなわちプロトコルを踏まえるのがならわしです。破ると、場合によっては外交問題になります。]

=== 相手がいる実世界の例: スーパーに梅干しの在庫を問い合わせる

プロトコルについて考えるため、
例としてスーパー「なるえつ」に大山の梅干しの在庫があるかを確認するために携帯電話から電話をかけたとしましょう。

通話して相手につながりました。
さてそこで、相手が
"Hello, this is Mike. How can I help you?"
と言ってきたとします。
日本語での応答を期待していたとすると、これは困ります。
@<fn>{mike_is_kind}

//footnote[mike_is_kind][日本語で言うと「私はマイクです。何かお手伝いできることはありますか」と言っています。2文目は英語の顧客サポートでしばしば聞く表現で、つまり、多分ですが、この窓口は接客のための窓口で、マイクは、可能性として、なるえつのサポートかもしれません。でも店名言ってません。というわけで筆者なら"Well, am I speaking to Naruetsu Supermarket?"とか聞くような気がしますが、やっぱり勘弁です。]

日本語でスーパーに対して大山の梅干しを問い合わせる場合、
大まかに以下のような流れになるでしょう。

 * 「はい、スーパーなるえつです」
 * 「名前も名乗らぬ客です。大山の梅干しはありますか」
 * 「少々お待ちください……在庫ありました」
 * 「ありがとうございますガチャっ」

ラフに書けばこのくらいの応答がありえます。

インターネット上でもこのやりとりと似たことが行われています。
まず冒頭のサーバ側の返答で、クライアントは少なくとも相手が「スーパーなるえつ」と名乗っていることを理解します。
@<fn>{certificate_for_naruetsu}

//footnote[certificate_for_naruetsu][厳密にはスーパーなるえつであるかの証明書が欲しいところです]

次に客は「私は認証されていないユーザです」と延べ、後述するHTPのGETかHEADに相当する形で「大山の梅干し」の在庫確認のクエリを送っています。
「少々お待ちください」はおいとくとして、少なくともその要求に対してリソースがあることまではスーパーなるえつサーバは応答します。

残念ながらインターネットのようにデータを直接受け取ることはできないので、
ここで電話のやりとりは終わりにして、実際に店舗に行った時に売り切れている恐怖と戦います。

=== プロトコルとは異なる相手同士が先に決めといた約束

プロトコルとは、特にコンピュータの分野では、実際に異なる相手同士がやりとりをする約束事のことです。
Webサーバにしろ何にしろ、インターネット上でクライアントとサーバが通信するには、
何らかのプロトコルが必要になります。

ちなみにアプリ開発と同様、両方自分が作っている場合に限っては、
プロトコルは自由に変更出来るでしょう。
しかし一般的には相手は別の会社のサーバだったり、政府のそれだったりするので、
ルールに基づいてアクセスしないと、無視されたり、あるいは悪者扱いされます。

=== 一つのプロトコルの上に動作するプロトコル

実際には「ネットワーク」の章でもTCP/IPなどのプロトコルを勉強しているかもしれません。
TCPもIPもPは"Protocol"です。
WebサーバはすでにTCP/IPというプロトコルを守ってるのではないでしょうか。

ではなるえつの例にちょっと戻ります。
なるえつと梅干しの例では最初、電話の受け取り側（サーバーです！）は電話の応答口が「スーパーなるえつ」であると言っています。
ここで、電話は通じていることが隠れた重要な前提です。

お店によっては、電話番号を公開してなかったり、支払いを忘れて電話が止められてたりします。
在庫確認はFAXでおねがいします、というスーパーもあるかもしれません。

さて、先ほどの例は、電話がつながることを前提としつつ、
電話がつながったからといって意思疎通ができるとは限らないことを示したものです。

なるえつに電話がつながった瞬間、相手が突然
「今朝、丸ノ内線で、すずらんの花が咲きました」と語りだしたら、客はマジで困ります。
歌を歌われたらもっと困ります。
客の我慢にも限度があります。

「電話がつながる」ことと「必要な情報を得られる」ことの間にはまだ隔たりがあるわけです。

「電話がつながる」ところまでが、言ってみればTCP/IPが保証している領域、
と考えるのが今はわかりやすいと思います。
最初に相手につながること、これ自体がまず何らかの取り決めの上になりたっています。
TCP/IPが担うのは、言ってみればそこです。

しかし「TCP/IP」といったプロトコルだけでは、Webサーバ上のデータをやりとりするのには不足です。
電話がつながっても、日本語である必要があるし、
日本語にしても適切な応対の幅があるというのもわかります（梅干しがなければ「ない」と答えます。）@<fn>{osi}

//footnote[osi][TCP/IPについて本当に前章で説明されているのか知らずに書いてますが、ついでに「OSI参照モデル」という言葉も紹介しておきます。なるえつの例で、ネットワークの授業の上で重要な点は「電話」と「その上でなされる会話」は別のレイヤ（層）に分けて考えることができる、ということです（在庫確認は電話でなくても出来ますね。）つきつめていくと、インターネット上でのやりとりは「7つの層」で説明できると考えるのがOSI参照モデルです。ぐぐるといっぱい出てきますので、このあたりの説明は、これで。]

=== コンピュータどうしのやりとりでは「プロトコル」はさらに大事

なるえつの例では、ある程度プロトコル（しきたり）みたいなものがある程度あるといっても、
相手の応答がおかしければ人間同士でなんとかする余地がありました。
相手がすずらんのことを話し始めたら
「焦るな。俺は大山の梅干しが食べたいだけなんだ。」
と返答すれば、もしかすると相手は正気に戻るかもしれません。

しかしコンピュータは、人間以上にアドリブに大変弱いです。空気を読めません。
@<fn>{chainber}

//footnote[chainber][コンピュータに「彼はなんと言っている！？」と聞いたときに丁寧に空気を読む回答をしてくるとすれば、そのコンピュータはチューリングテストにそのまま合格出来そうです。チューリングテストとはある機械が知的かどうか（人工知能であるかどうか）を判定するためのテストのことです（Wikipedia日本語版「チューリング・テスト」参照）]

コンピュータにおけるサーバとクライアントのやりとりでは、想定外の事態を含めていろいろな状況が起こりえます。
その状況を可能な限り網羅したプロトコル（つまりルール）を全て準備しておき、
クライアントとサーバの両方がそのプロトコルにしたがってデータを要求してデータを受け取る必要があります。
@<fn>{p2p_is_harder}

//footnote[p2p_is_harder][P2Pは、一般的にはサーバ・クライアントモデルよりも面倒な状況がさらに増える傾向があります。例えばWebをP2P的にしようとすると、WebブラウザはWebサーバ「としても」振る舞う必要が出てきますし、逆もしかり。]

== Web

ここまでで「サーバ」については分かりました。
でも私達が知りたいのは「Webサーバ」です。

webという英単語は、もともと「蜘蛛の巣」を意味しています。

この用語に絡めて、1990年にスイスのCERNという研究所に所属していた
Tim Berners-Lee博士がWorldWideWebを提唱したのがこの言葉の始まりです。@<fn>{internet_existed_before_www}
博士は世界に分散した情報（特に当初は技術論文）を皆が共有して相互に閲覧できるよう、
文書内のリンクを介してインターネットに接続された世界中の情報が、蜘蛛の巣のように密につながり、
情報を共有出来る状態になる未来を期待し、どのような要素が必要か、といった点について、世界に対する提案書を公開しました。@<fn>{www_proposal}
このあと"Mosaic"と呼ばれるWebブラウザの登場もあって、Webの利用は爆発的に普及し、今に至ります。

//footnote[internet_existed_before_www][情報共有を行う手段自体は1990年以前から存在しました。例えばWikipediaの「電子メール」の記事によれば1965年に世界最初の電子メールが使われ始めた、とあります。]
//footnote[www_proposal][最初の提案をW3C（The World Wide Web Consotium）のWebサイト@<href>{http://www.w3.org/Proposal.html}で読むことが出来ます。ブログやTwitterどころかWebページという概念が一般に存在しない時代のことです。]

Webでは、相互にリンクのある「ハイパーテキスト」をWebサーバに配置し、それを人がWebブラウザで見るという用途が一般的でした。
HTML（Hyper Text Markup Language）は、その名前が示す通り「ハイパーテキスト」ためのマークアップ言語@<fn>{markup_language}です。
また、世界中に散らばったハイパーテキストがどこにあるかを「ハイパーテキスト」（HTML）に記述できなければなりません。
というわけで、Webの世界ではURI（Universal Resource Identifier）が大変重要です。
そして、URIも込みで記述されたHTMLをクライアントであるWebブラウザが要求してWebサーバが返答するやりとり自体に用いるプロトコルとして
HTTP（Hyper Text Transfer Protocol）の各種バージョンを用います。その名前が示す通り「ハイパーテキスト」を転送するプロトコルです。

というわけで、Webを理解する上で、HTPとHTMLとURIが、まず最重要の技術やプロトコルということがわかってきます。

//footnote[markup_language][マークアップ言語は「文章の構造（段落など）や見栄え（フォントサイズなど）に関する指定を文章とともにテキストファイルに記述するための言語」です。（Wikipedia日本語記事より）有名なものとしてHTMLがあります！]

=== HTML

=== URI

=== HTTP

Webサーバの場合にTCP/IPの上で使われるのは、
HTTP（Hypertext Transfer Protocol）というプロトコルです。

このプロトコルの詳細はRFCと呼ばれる仕様書により定義されます。

RFCはRequest For Commentsの略です。
IETF（Internet Engineering Task Force）と呼ばれる
組織によって発行される、技術仕様等に関する文書を指します。
IETFは特にインターネットで利用される標準について議論を行う組織です。
議論する対象に応じてワーキンググループを作成し、
メーリングリストでの議論の後、RFCを発行するなどして
そのワーキンググループの活動を一旦終了します。
TCP/IPに関わる仕様もIETF由来です。
RFCの詳細については本章ではここまでにしておき、次章へ譲ります。

Webサーバとやりとりする基本的なプロトコルであるHTTPでは、
クライアントからサーバへ要求（リクエスト、request）を送り、
サーバがそれに対する応答（レスポンス、response）を返します。


リクエストの種類について、HTTPにはたくさんの種類がありますが、
まず最初に学ぶべきは「GET」リクエストと「POST」リクエストです。
両方共クライアント、つまりWebクライアントの側から送るリクエストの種類です。

==== GETリクエスト

==== POSTリクエスト

==== レスポンス

HTTPにおいて、WebブラウザやAndroidアプリのようなクライアントからリクエストを送った際、
Webサーバはその要求に対して自分の状態を確認し、適切なな返答を返します。
合わせて、Webサーバがどのようなタイプのデータを返すかを示す
Content-Type と呼ばれる情報と、実際のデータ（Content）を返します。
Contentは「中身」です。@<footnote>{contents}

//footnote[contents][ちなみに日本語でも「コンテンツ」という表現で使われますが、これはWebページの中身やエンターテイメントのような商品のニュアンスがありますね。ここではあくまで送られてくるデータの中身のことです。]

非常に典型的なのは「このWebページですね。どうぞ」と
「そんなWebページ、ない」という2種類の応答です。

Webサーバのそれぞれのレスポンスに対しては3桁の数字が割り振られます。
それぞれ、3桁目が主要な理由を示しており、残りの2桁でより具体的になります。

上の例で言えば「このWebページですね、どうぞ」は200番「OK」です。
「そんなWebページ、ない」は404番です。
これらの意味は皆RFCに記載されています。

本章では立ち入りませんが、レスポンスコードはプロトコルで規定されていつつも、
歴史上の理由でしばしば仕様通りに返答を返してくれないWebサーバもあります。
ここでは「仕様無視！そういうのもあるのか」という程度で軽く理解しておくことにしましょう。

#@warn(TODO: 実際にリクエストの中身とレスポンスの中身を平文で書く。telnetの結果みたいなもの)

== 進化し続けるWeb

現在のWebは、WebブラウザによるWebサイト閲覧にとどまらない幅広い用途に使われています。
これまで説明した、当初のWebから考えるとある意味で「用途違い」のものにまで応用されるのが当たり前になっています。

例えば『Webを支える技術』では、現在のWebの用途を大きく分けて3つに分けて考えています。

 * Webサイト
 * ユーザインターフェースとしてのWeb@<fn>{web_as_ui}
 * プログラム用APIとしてのWeb

//footnote[web_as_ui][家庭用ルータの設定画面やHTMLヘルプ等を「Webサイト」と分けています。Webサーバを介した用途異なるというという意味で、そのとおりです。]

古くから意図されていたと思えるのは2番目、広く捉えても2番目までです。

しかし3番目の用途が、ある意味では現在のWebサーバとAndroidアプリにおける重要なポジションを占めます。

見方を変えてAndroidアプリの観点からは、以下の様になるでしょう

 * 外部WebサーバにHTMLを取得し、WebView（もしくはWebブラウザ）で表示する
 * 端末（アプリ）に保存されたHTMLをWebView（もしくはWebブラウザ）で表示する
 * WebサーバからXMLやJSONを取得し、アプリで利用する

さてこの3つの用途の中で「Webサーバ」が絡むのは1番目と3番目です。
1番目はあくまでWebブラウザ風のインターフェースをWebサーバから提供してもらう目的ですが、
3番めはデータだけとってきて、それをAndroidアプリで加工する目的が前提になっています。

#@warn(TODO: XMLやJSONを使うことの特長をもうすこし書く)


=== XML, SOAP, JSON, REST

WebブラウザとWebサーバというくくりでは、人がコンピュータにアクセスし、
HTMLを見るのが前提でした。

しかし3番目の用途はコンピュータがコンピュータにデータを取りに行きます。
HTMLは人が読む「ハイパーテキスト」ですが、はっきり言えば人が読める必要はありません。

コンピュータはHTMLの中の「この文章は強調して！」よりも
そのデータが何であるかを知りたいと思います。
「3月29日の12時からの14時までの天気予報」のデータを受け取るにしても、
ユーザはお天気マークが欲しいかもしれませんが、
コンピュータはお天気マークを記号化した"RAINY_BLUE"といった文字列
だけくれたほうが嬉しかったりします。
そのデータが、コンピュータがやりとりしやすいよう構造化されているに
越したことはありません。

WebブラウザでWebページを見る場合、多くの場合HTMLが返されます。
しかしAndroid端末が情報を取得するばあい、
人が見るために整形されたHTMLを取得するのは冗長です。

そのため、機械が読み取りやすいデータ形式として、
しばしばXMLとJSONという形式を見ることになるでしょう。

HTTPではWebサーバがContent-Type と呼ばれる情報を返してクライアントに返答する
データの種類を返答します。ここで、HTMLではなくXMLやJSONを返答することが可能です。
@<fn>{http_is_used_for_json}

//footnote[http_is_used_for_json][この場合、HTTP（@<b>{Hyper Text} Transfer Protocol）はもはやハイパーテキストを送るという当初の役割を超えて利用されることになります。]

=== ステートレスなHTTPとCookie

HTTPはもともと「ステートレスなプロトコル」と言われます。
HTTPの仕様の中には「前回の状態をサーバやクライアントは覚えておいてね♪」と要求している項目がないという意味です。

ここでハンバーガ屋と得意客の例を考えてみます。

#@warn(TODO: このハンバーガ屋の例はステートの意味を取り違えている。変える)

ハンバーガ屋に行き「ツケといてくれ、旦那」と客が支払いを後回しにもできるのがステートフルです。
「ステートフル」は英語でStatefulで、「状態を保持している」という意味です。
ハンバーガ屋は客のツケの金額等を覚えておく必要があります。

ステートフルな場合、次に行った時「この前のツケ、払ってくださいよ」と言うことができるように、
ツケという状態をハンバーガ屋が覚えておけるのが、ステートフルの一見したところ良い点です。
しかし、江戸時代からある下町のハンバーガ屋がお得意客数名に対してこれを行えても、最近の全国チェーンでこれは無理と言えます。
ステートを保持するのはコストがかかります。

というよりも全国チェーンでは「40分後に取りに来ますのでその時に出して」というステートだって、割と断られます。
非常にたくさんのお客を相手にうまくサービスを行き渡らせるには、客は逃げ出さない前提でその場で払ってその場でものをもらうのが通例です。
つまり、自動販売機のように前のことを何も覚えていないのがステートレスです。@<fn>{stateful_burger}

//footnote[stateful_burger][ちなみにこの無理矢理な例で言うと、番号札を渡して店員が後から席に持っていくモデルは、十分ステートフルなサーバです。しかし秒間1万リクエストくらい来る先進的なハンバーガ屋だとこれすら無理です。ステートレス・バーガーが素晴らしいわけです]

しかし実際にWebサーバを介してアクセスすると、
多くのWebサービスでは、ユーザ名とパスワードなど、いろいろなものをWebサーバが記憶しているように見えます。
特に、ブラウザを閉じてもそれらが残っているのは驚きです。

この大方の欲求に対処するのがCookieと呼ばれる仕組みです。
RFC 6265が参照できる仕様ですが、歴史的事情で完全にこのRFCの通りには動作しないとのことです。
@<fn>{rfc6265}

//footnote[rfc6265][Webではしばしばこういう話があります。次の章でもっと生々しい話をご紹介します。]


== 演習: Android アプリからWebサーバにアクセスしてみよう

さて、ここでは実際にAndroid経由でHTTPアクセスをしてみましょう。
ここでは@<code>{java.net.HttpURLConnection}を用いることにします。

#@warn(ネットワークの章でWebサーバへアクセスする事例は終了している可能性が高い。要調整)

===[column] DefaultHttpClientとAndroidHttpClient について

HTTPアクセスを行うライブラリは他にも@<code>{org.apache.http.impl.client.DefaultHttpClient}や
@<code>{android.net.http.AndroidHttpClient}といったライブラリが紹介されることがあります。
しかし本稿ではそれらの理由はおすすめしません。
現時点でこれらの実装にはバグが多く、今後もメンテナンスされる見込みがないと考えられているためです。
なお、非常に古いAndroidのバージョン（2.2）では@<code>{java.net.HttpURLConnection}にバグがあったため、
それらの古いバージョンでは注意が必要です。

 * 参考: Android Apache HTTP Client と HttpURLConnection どっちを使うべき？ @<href>{http://y-anz-m.blogspot.jp/2011/10/androidapache-http-client.html}@<fn>{this_is_also_old_article}

//footnote[this_is_also_old_article][記事の公開2011年10月4日に公開された点も出来れば]

== 実習: 天気の情報を取ってくる

== その他のサーバ

本章を始めとする一連の説明は、Webサーバについての説明を中心としています。
しかしインターネット・クラウド上にあるサーバはそれだけにとどまりません。

 * メールサーバ
 * ファイルサーバ
 * プリントサーバ

「プリントサーバ」について補足しましょう。

Word文書を印刷したりするために、プリンタを利用することは多いと思います。
昔のプリンタはUSB接続やその他の接続でPC1台とつながりませんでした。
しかし業務用プリンタや最近のプリンタは賢く、
複数台のパソコンやAndroid端末などから「このデータを印刷して」という要求を受けて、印刷を行います。
リクエストを受けて、レスポンスとして印刷するので、これもサーバです。

Webサーバと通信するためにプロトコルとして「HTTP」が重要でした。
同様に、各サーバではその用途に応じてプロトコルが必要です。

 * メールサーバ ... POP, IMAP, SMTPなど
 * プリントサーバ ... IPP, LPRなど
 * ファイルサーバ ... SMBなど

全てではありませんが、これらのプロトコルの多くも仕様、特にRFCで規定されたりします。@<fn>{not_rfc}

//footnote[not_rfc][インターネット上で利用されるプロトコルの全ての仕様が完全に公開されるとは限りません。通信する相手同士が合意するためのルールがプロトコルですから、合意が秘密裏に行われていても動作すればその二者（二社）にとっては十分と言えます。その場合はそれを知らない人が参加できないので、「ケチ」とか「いじわる」とか言われますが、合意の難易度は場合によっては飛躍的に下がることもあります。この点については次章でもう少し考えます]

== まとめ

本章ではWebサーバと通信する上で必要な基礎知識について説明しました。

次章では本章を下敷きにして、紹介した技術の深淵を見ていきます。
