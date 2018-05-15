<h1>Hot to use cli_wallet</h1>

<h5><a href="https://github.com/news-chain/newschain/releases/tag/cli_wallet" target="blank">release download</a></h5>

<pre><code>#lanuch cli_wallet
./cli_wallet --server-rpc-endpoint=&quot;ws://47.100.220.100:7000&quot; --rpc-endpoint=&quot;127.0.0.1:8080&quot; --rpc-http-allowip=&quot;127.0.0.1&quot;

#--server-rpc-endpoint  区块链服务器节点（必选参数）
#--rpc-endpoint         钱包服务器业务节点 （可选）
#--rpc-allowip          ip限制参数</code></pre>

<h1>命令行使用</h1>

<h3>设置钱包密码</h3>

<pre><code>step1：new &gt;&gt; set_password 123456      </code></pre>

<h3>钱包解锁</h3>

<pre><code>step2:locked &gt;&gt; unlock 123456          </code></pre>

<h3>导入用户key， 用户名为newcoin ，newcoin为测试账户</h3>

<pre><code>step3:unlocked &gt;&gt; import_key 5JG2b4VBLLaMFLzsxz57NjRC3hNSo2GyZ6W7DAQS7xdtn4Z12kg    </code></pre>

<h3>创建用户</h3>

<pre><code>step4：create_account &quot;newcoin&quot; &quot;sswer123&quot; &quot;&quot; true

上链成功返回：
2487654ms th_a       wallet.cpp:460                save_wallet_file     ] saving wallet to file wallet.json
2487655ms th_a       wallet.cpp:460                save_wallet_file     ] saving wallet to file wallet.json
2487656ms th_a       wallet.cpp:460                save_wallet_file     ] saving wallet to file wallet.json
2487658ms th_a       wallet.cpp:460                save_wallet_file     ] saving wallet to file wallet.json
2487694ms th_a       wallet.cpp:635                sign_transaction     ] v_approving_keys: [&quot;NT6B6PzKeh1BLcCnfJA7CR4d8BGxQzrVEKtEMxY67RxNtdJtBY9X&quot;] 
2487694ms th_a       wallet.cpp:637                sign_transaction     ] approving_key: NT6B6PzKeh1BLcCnfJA7CR4d8BGxQzrVEKtEMxY67RxNtdJtBY9X 
{
  &quot;ref_block_num&quot;: 36622,
  &quot;ref_block_prefix&quot;: 2127126422,
  &quot;expiration&quot;: &quot;2018-05-15T11:41:57&quot;,          //时间
  &quot;operations&quot;: [[
      &quot;account_create&quot;,{
        &quot;fee&quot;: &quot;0.000 NEWT&quot;,
        &quot;creator&quot;: &quot;newcoin&quot;,                   //creator 地址
        &quot;new_account_name&quot;: &quot;sswer123&quot;,         //用户地址
        &quot;parentNode&quot;: &quot;&quot;,
        &quot;owner&quot;: {
          &quot;weight_threshold&quot;: 1,
          &quot;account_auths&quot;: [],
          &quot;key_auths&quot;: [[
              &quot;NT7hkaxn1byxnDs6U7Dvdi6nigCNixoBeJJKhmy4BcTyR9ydDfgP&quot;,       //公钥
              1
            ]
          ]
        },
        &quot;active&quot;: {
          &quot;weight_threshold&quot;: 1,
          &quot;account_auths&quot;: [],
          &quot;key_auths&quot;: [[
              &quot;NT6tj1wA4j9GYbW9zZ2czwWJ3uU8VFU6sk5XBzuGCh8x87jM68cA&quot;,
              1
            ]
          ]
        },
        &quot;posting&quot;: {
          &quot;weight_threshold&quot;: 1,
          &quot;account_auths&quot;: [],
          &quot;key_auths&quot;: [[
              &quot;NT4wWKqdzXWeXf6sTRRW7zQ6r8pge64ug1P9VWez2WDu4CVX67QZ&quot;,
              1
            ]
          ]
        },
        &quot;memo_key&quot;: &quot;NT7eaj1H3qe3w52v8RL7CktBebfNF66Ce5dtQiX2gbU5wFCg2HDx&quot;,
        &quot;json_metadata&quot;: &quot;&quot;
      }
    ]
  ],
  &quot;extensions&quot;: [],
  &quot;signatures&quot;: [
    &quot;204ac0c4cabc30402d6e459397411c8b3e6931b229ac83a0a46ecfbcfe320731f74032ee9eedcdc42715e0639c90322cb691108d004dc946ae7ead49815427d3a4&quot;
  ],
  &quot;transaction_id&quot;: &quot;b15928ba56d55ddd2b149c844bcd568cd1034cfd&quot;,     //trxid
  &quot;block_num&quot;: 233231,                                              //区块号
  &quot;transaction_num&quot;: 0
}</code></pre>

<h3>转账</h3>

<pre><code>etc1:转账
    transfer &quot;newcoin&quot; &quot;sswer123&quot; &quot;1.000 NEWT&quot; &quot;memo&quot; true
    @param newcoin      转出用户
    @param sswer123     转入用户
    @param 1.000 NEWT   金额
    @param memo         转账备注
    @param true         进行广播</code></pre>

<h3>查询</h3>

<pre><code>etc1：查询用户余额
    get_account &quot;sswer123&quot;
    @param &quot;sswer123&quot;  查询用户名
    返回值：
    {
      &quot;id&quot;: 115510,         //用户id
      &quot;name&quot;: &quot;sswer123&quot;,   //用户名
      &quot;owner&quot;: {
        &quot;weight_threshold&quot;: 1,
        &quot;account_auths&quot;: [],
        &quot;key_auths&quot;: [[
            &quot;NT7hkaxn1byxnDs6U7Dvdi6nigCNixoBeJJKhmy4BcTyR9ydDfgP&quot;,     //公钥
            1
          ]
        ]
      },
      &quot;active&quot;: {
        &quot;weight_threshold&quot;: 1,
        &quot;account_auths&quot;: [],
        &quot;key_auths&quot;: [[
            &quot;NT6tj1wA4j9GYbW9zZ2czwWJ3uU8VFU6sk5XBzuGCh8x87jM68cA&quot;,
            1
          ]
        ]
      },
      &quot;posting&quot;: {
        &quot;weight_threshold&quot;: 1,
        &quot;account_auths&quot;: [],
        &quot;key_auths&quot;: [[
            &quot;NT4wWKqdzXWeXf6sTRRW7zQ6r8pge64ug1P9VWez2WDu4CVX67QZ&quot;,
            1
          ]
        ]
      },
      &quot;memo_key&quot;: &quot;NT7eaj1H3qe3w52v8RL7CktBebfNF66Ce5dtQiX2gbU5wFCg2HDx&quot;,
      &quot;json_metadata&quot;: &quot;&quot;,
      &quot;proxy&quot;: &quot;&quot;,
      &quot;last_owner_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;last_account_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;created&quot;: &quot;2018-05-15T11:41:27&quot;,
      &quot;mined&quot;: false,
      &quot;owner_challenged&quot;: false,
      &quot;active_challenged&quot;: false,
      &quot;last_owner_proved&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;last_active_proved&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;recovery_account&quot;: &quot;steem&quot;,
      &quot;last_account_recovery&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;reset_account&quot;: &quot;null&quot;,
      &quot;comment_count&quot;: 0,
      &quot;lifetime_vote_count&quot;: 0,
      &quot;post_count&quot;: 0,
      &quot;can_vote&quot;: true,
      &quot;voting_power&quot;: 10000,
      &quot;last_vote_time&quot;: &quot;2018-05-15T11:41:27&quot;,
      &quot;balance&quot;: &quot;1.000 NEWT&quot;,              //用户余额
      &quot;savings_balance&quot;: &quot;0.000 TESTS&quot;,
      &quot;sbd_balance&quot;: &quot;0.000 TBD&quot;,
      &quot;sbd_seconds&quot;: &quot;0&quot;,
      &quot;sbd_seconds_last_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;sbd_last_interest_payment&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;savings_sbd_balance&quot;: &quot;0.000 TBD&quot;,
      &quot;savings_sbd_seconds&quot;: &quot;0&quot;,
      &quot;savings_sbd_seconds_last_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;savings_sbd_last_interest_payment&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;savings_withdraw_requests&quot;: 0,
      &quot;reward_sbd_balance&quot;: &quot;0.000 TBD&quot;,
      &quot;reward_steem_balance&quot;: &quot;0.000 TESTS&quot;,
      &quot;reward_vesting_balance&quot;: &quot;0.000000 VESTS&quot;,
      &quot;reward_vesting_steem&quot;: &quot;0.000 TESTS&quot;,
      &quot;vesting_shares&quot;: &quot;0.000000 VESTS&quot;,
      &quot;delegated_vesting_shares&quot;: &quot;0.000000 VESTS&quot;,
      &quot;received_vesting_shares&quot;: &quot;0.000000 VESTS&quot;,
      &quot;vesting_withdraw_rate&quot;: &quot;0.000000 VESTS&quot;,
      &quot;next_vesting_withdrawal&quot;: &quot;1969-12-31T23:59:59&quot;,
      &quot;withdrawn&quot;: 0,
      &quot;to_withdraw&quot;: 0,
      &quot;withdraw_routes&quot;: 0,
      &quot;curation_rewards&quot;: 0,
      &quot;posting_rewards&quot;: 0,
      &quot;proxied_vsf_votes&quot;: [
        0,
        0,
        0,
        0
      ],
      &quot;witnesses_voted_for&quot;: 0,
      &quot;average_bandwidth&quot;: 0,
      &quot;lifetime_bandwidth&quot;: 0,
      &quot;last_bandwidth_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;average_market_bandwidth&quot;: 0,
      &quot;lifetime_market_bandwidth&quot;: 0,
      &quot;last_market_bandwidth_update&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;last_post&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;last_root_post&quot;: &quot;1970-01-01T00:00:00&quot;,
      &quot;parentNode&quot;: &quot;&quot;,
      &quot;level&quot;: {
        &quot;readerLevel&quot;: 1,
        &quot;readerPercent&quot;: 0,
        &quot;writeLevel&quot;: 1,
        &quot;writePercent&quot;: 0,
        &quot;shareLevel&quot;: 1,
        &quot;sharePercent&quot;: 0
      }
    }

etc2：查询用户历史记录
    get_account_history &quot;sswer123&quot; -1 100
    @param sswer123     查询用户名
    @param index        查询最新传-1,
    @param limit        查询条数，上限为1000
    返回结果：

    #序号     BLOCK #    TRX ID交易id        OPERATION 操作类型           DETAILS                               
    -------------------------------------------------------------------------------
    1     233231     b15928ba56d55ddd2b149c844bcd568cd1034cfd account_create       {&quot;fee&quot;:&quot;0.000 NEWT&quot;,&quot;creator&quot;:&quot;newcoin&quot;,&quot;new_account_name&quot;:&quot;sswer123&quot;,&quot;parentNode&quot;:&quot;&quot;,&quot;owner&quot;:{&quot;weight_threshold&quot;:1,&quot;account_auths&quot;:[],&quot;key_auths&quot;:[[&quot;NT7hkaxn1byxnDs6U7Dvdi6nigCNixoBeJJKhmy4BcTyR9ydDfgP&quot;,1]]},&quot;active&quot;:{&quot;weight_threshold&quot;:1,&quot;account_auths&quot;:[],&quot;key_auths&quot;:[[&quot;NT6tj1wA4j9GYbW9zZ2czwWJ3uU8VFU6sk5XBzuGCh8x87jM68cA&quot;,1]]},&quot;posting&quot;:{&quot;weight_threshold&quot;:1,&quot;account_auths&quot;:[],&quot;key_auths&quot;:[[&quot;NT4wWKqdzXWeXf6sTRRW7zQ6r8pge64ug1P9VWez2WDu4CVX67QZ&quot;,1]]},&quot;memo_key&quot;:&quot;NT7eaj1H3qe3w52v8RL7CktBebfNF66Ce5dtQiX2gbU5wFCg2HDx&quot;,&quot;json_metadata&quot;:&quot;&quot;}
     2     233983     10ca6fe8ed7f872771e872d74263c1554d86824e transfer             {&quot;from&quot;:&quot;newcoin&quot;,&quot;to&quot;:&quot;sswer123&quot;,&quot;amount&quot;:&quot;1.000 NEWT&quot;,&quot;memo&quot;:&quot;memo&quot;}
     3     234031     bb8380557a438ce97132c4e5c699a1056b9ffcae transfer             {&quot;from&quot;:&quot;sswer123&quot;,&quot;to&quot;:&quot;newcoin&quot;,&quot;amount&quot;:&quot;1.000 NEWT&quot;,&quot;memo&quot;:&quot;test&quot;


etc3：查询当前钱包的所有用户
    list_my_accounts
    @param  无参数</code></pre>

<h3>其他</h3>

<pre><code>etc1：获取最新块号
     info
    成功返回：
    {
      &quot;id&quot;: 0,
      &quot;head_block_number&quot;: 234181,  //当前返回块号
      &quot;head_block_id&quot;: &quot;000392c5bf463ecf95a98144354dc6d40167e998&quot;,      //块id
      &quot;time&quot;: &quot;2018-05-15T12:29:00&quot;,
      &quot;current_witness&quot;: &quot;newcoin&quot;,                                     
      &quot;total_pow&quot;: &quot;18446744073709551615&quot;,
      &quot;num_pow_witnesses&quot;: 0,
      &quot;virtual_supply&quot;: &quot;0.000 TESTS&quot;,
      &quot;current_supply&quot;: &quot;0.000 TESTS&quot;,
      &quot;confidential_supply&quot;: &quot;0.000 TESTS&quot;,
      &quot;current_sbd_supply&quot;: &quot;0.000 TBD&quot;,
      &quot;confidential_sbd_supply&quot;: &quot;0.000 TBD&quot;,
      &quot;total_vesting_fund_steem&quot;: &quot;0.000 TESTS&quot;,
      &quot;total_vesting_shares&quot;: &quot;0.000000 VESTS&quot;,
      &quot;total_reward_fund_steem&quot;: &quot;0.000 TESTS&quot;,
      &quot;total_reward_shares2&quot;: &quot;0&quot;,
      &quot;pending_rewarded_vesting_shares&quot;: &quot;0.000000 VESTS&quot;,
      &quot;pending_rewarded_vesting_steem&quot;: &quot;0.000 TESTS&quot;,
      &quot;sbd_interest_rate&quot;: 1000,
      &quot;sbd_print_rate&quot;: 10000,
      &quot;maximum_block_size&quot;: 1048576,
      &quot;current_aslot&quot;: 24926980,
      &quot;recent_slots_filled&quot;: &quot;340282366920938463463374607431768211455&quot;,
      &quot;participation_count&quot;: 128,
      &quot;last_irreversible_block_num&quot;: 234160,                        //不可逆的块号
      &quot;vote_power_reserve_rate&quot;: 40,
      &quot;current_reserve_ratio&quot;: 200000000,
      &quot;average_block_size&quot;: 119,
      &quot;max_virtual_bandwidth&quot;: &quot;4227858432000000000000&quot;,
      &quot;witness_majority_version&quot;: &quot;0.0.0&quot;,
      &quot;hardfork_version&quot;: &quot;0.5.0&quot;,
      &quot;head_block_num&quot;: 234181,
      &quot;head_block_age&quot;: &quot;2 seconds old&quot;,
      &quot;participation&quot;: &quot;100.00000000000000000&quot;,
      &quot;median_sbd_price&quot;: {
        &quot;base&quot;: &quot;1.000 TESTS&quot;,
        &quot;quote&quot;: &quot;0.800 TBD&quot;
      },
      &quot;account_creation_fee&quot;: &quot;0.000 NEWT&quot;
    }


etc2：获取版本信息
    abount
    成功返回：
    unlocked &gt;&gt;&gt; about
    {
      &quot;blockchain_version&quot;: &quot;0.19.3&quot;,
      &quot;client_version&quot;: &quot;unknown&quot;,
      &quot;steem_revision&quot;: &quot;e8565cb8058ed9ec74bde2ea553c2e95e5c6f754&quot;,
      &quot;steem_revision_age&quot;: &quot;47 days ago&quot;,
      &quot;fc_revision&quot;: &quot;c009d2d8332a3ce9936c00deb6f4629555f26fad&quot;,
      &quot;fc_revision_age&quot;: &quot;37 weeks ago&quot;,
      &quot;compile_date&quot;: &quot;compiled on May 12 2018 at 19:40:53&quot;,
      &quot;boost_version&quot;: &quot;1.60&quot;,
      &quot;openssl_version&quot;: &quot;OpenSSL 1.0.2n  7 Dec 2017&quot;,
      &quot;build&quot;: &quot;linux 64-bit&quot;,
      &quot;server_blockchain_version&quot;: &quot;0.19.3&quot;,
      &quot;server_steem_revision&quot;: &quot;e8565cb8058ed9ec74bde2ea553c2e95e5c6f754&quot;,
      &quot;server_fc_revision&quot;: &quot;c009d2d8332a3ce9936c00deb6f4629555f26fad&quot;
    }</code></pre>

<h3>钱包业务端口使用</h3>

<pre><code>curl &quot;127.0.0.1:8080&quot; -d &quot;{\&quot;id\&quot;:8,\&quot;method\&quot;:\&quot;transfer\&quot;,\&quot;params\&quot;:[\&quot;newcoin\&quot;, \&quot;twerw123414\&quot;, \&quot;1.000 NEWT\&quot;, \&quot;\&quot;, true]}&quot;

说明：        
发送http ， post 请求
{&quot;id&quot;:8,&quot;method&quot;:&quot;transfer&quot;,&quot;params&quot;:[&quot;newcoin&quot;, &quot;twerw123414&quot;, &quot;1.000 NEWT&quot;, &quot;&quot;, true]}
参数解释：
@param id       ： 请求id，int都可以
@param method   ： 调用方法
@param params   ： 方法对应参数

钱包接口请求和命令行请求一致。填入对应的参数。

</code></pre>