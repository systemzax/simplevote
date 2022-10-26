# simplevote

Simplevote is a simple permissioned messaging system to establish a public record of deliberations between chains participating to the common EOSIO core development effort.

# configuration

`cleos push action simplevote addchain '{"chain":"EOS", "owner":"myaccount"}' -p simplevote`

Adds a chain with associated owner to the contract. Requires contract authorization.

`cleos push action simplevote changeowner '{"chain":"EOS", "newowner":"mynewaccount"}' -p myaccount`

Changes owner account for a given chain. Requires current owner authorization or contract authorization.

`cleos push action simplevote removechain '{"chain":"EOS"}' -p simplevote`

Removes chain and all associated voters. Requires chain owner authorization or contract authorization.

`cleos push action simplevote addvoter '{"chain":"EOS", "voter":"otheraccount"}' -p myaccount `

Adds a voter under a given existing chain. Requires chain owner or contract permission.

`cleos push action simplevote removevoter '{"chain":"EOS", "owner":"otheraccount"}' -p myaccount `

Removes a voter from a given existing chain. Requires chain owner or contract permission.

# usage

`cleos push action simplevote sendmsg '{"voter":"myaccount", "message":"some message"}' -p myaccount`

Publishes a message to the block log. Requires voter permission. 