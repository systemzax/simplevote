# simplevote

Simplevote is a simple permissioned messaging system to establish a public record of deliberations between chains participating to the common EOSIO core development effort.

# configuration

`cleos push action simplevote addchain '{"chain":"EOS", "owner":"myaccount"}' -p simplevote`

Adds a chain with associated owner to the contract.

`cleos push action simplevote changeowner '{"chain":"EOS", "owner":"myaccount"}'( symbol_code chain, name newowner) -p myaccount;`

`cleos push action simplevote removechain '{"chain":"EOS", "owner":"myaccount"}'( symbol_code chain);`

`cleos push action simplevote addvoter '{"chain":"EOS", "owner":"myaccount"}'( name voter, symbol_code chain);`

`cleos push action simplevote removevoter '{"chain":"EOS", "owner":"myaccount"}'( name voter);`

# usage

`cleos push action simplevote sendmsg '{"voter":"myaccount", "message":"some message"}' -p myaccount`