// Copyright 2019 Kyle F. Downey
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <spdlog/spdlog.h>

#include <cloudwall/crypto-mktdata/coinbase.h>
#include <uvw/loop.hpp>

using cloudwall::coinbase::marketdata::CoinbaseRawFeedClient;
using cloudwall::core::marketdata::Channel;
using cloudwall::core::marketdata::Currency;
using cloudwall::core::marketdata::CurrencyPair;
using cloudwall::core::marketdata::RawFeedMessage;

int main(int argc, const char *argv[]) {
    auto ccy_pair = CurrencyPair(Currency("BTC"), Currency("USD"));
    std::list<Channel> channels({
            Channel("status", { }),
            Channel("matches", ccy_pair),
            Channel("ticker", ccy_pair)
    });
    auto sub = Subscription(channels);
    const OnRawFeedMessageCallback& callback = [](const RawFeedMessage& msg) {
      spdlog::info("Incoming message: {}", msg.get_raw_json());
    };

    auto client = CoinbaseRawFeedClient(sub, callback);
    client.connect();
    spdlog::info("Coinbase Pro feed handler <READY>");

    auto loop = uvw::Loop::getDefault();
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        loop->run();
    }
#pragma clang diagnostic pop
}
