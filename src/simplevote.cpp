#include <simplevote.hpp>

//records message on chain
ACTION simplevote::sendmsg( name voter, std::string message) {

   auto v_itr = _voters.find(voter.value);

   check(v_itr!=_voters.end(), "voter not found");

   auto c_itr = _chains.find(v_itr->chain.raw());

   check(c_itr!=_chains.end(), "chain not found"); //should not happen

   require_auth(voter);


}

//add voter / chain
ACTION simplevote::addvoter( name voter, symbol_code chain) {

   auto c_itr = _chains.find(chain.raw());
   auto v_itr = _voters.find(voter.value);

   check(c_itr!=_chains.end(), "chain not found");
   check(v_itr==_voters.end(), "voter already exists");

   if (!has_auth(_self)){
      require_auth(c_itr->owner);
   }

   _voters.emplace( _self, [&]( auto& v ){
      v.voter = voter;
      v.chain = chain;
   });

}

//remove voter
ACTION simplevote::removevoter( name voter) {

   auto v_itr = _voters.find(voter.value);

   check(v_itr!=_voters.end(), "voter not found");

   auto c_itr = _chains.find(v_itr->chain.raw());

   check(c_itr!=_chains.end(), "chain not found");  //should not happen

   if (!has_auth(_self) && !has_auth(voter)){
      require_auth(c_itr->owner);
   }

   _voters.erase(v_itr);

}

//add chain
ACTION simplevote::addchain(symbol_code chain, name owner) {

   require_auth(_self);

   auto itr = _chains.find(chain.raw());

   check(itr==_chains.end(), "chain already exists");

   _chains.emplace( _self, [&]( auto& c ){
      c.owner = owner;
      c.chain = chain;
   });

   //triggers automatic addition of owner as voter
   action act_addvoter(
     permission_level{_self, "active"_n},
     _self, "addvoter"_n,
     std::make_tuple(owner, chain)
   );
   act_addvoter.send();

}

//change a chain's owner
ACTION simplevote::changeowner( symbol_code chain, name newowner) {
   
   auto itr = _chains.find(chain.raw());

   check(itr!=_chains.end(), "chain not found");

   if (!has_auth(_self)){
      require_auth(itr->owner);
   }

   _chains.modify( *itr, same_payer, [&]( auto& c ) {
      c.owner = newowner;
   });

}

//remove chain and chain voters from contract
ACTION simplevote::removechain( symbol_code chain) {

   auto itr = _chains.find(chain.raw());

   check(itr!=_chains.end(), "chain not found");

   if (!has_auth(_self)){
      require_auth(itr->owner);
   }

   _chains.erase(itr);

   auto chain_index = _voters.get_index<"chain"_n>();

   auto v_itr = chain_index.lower_bound(chain.raw());
   auto end_v_itr = chain_index.upper_bound(chain.raw() + 1);

   while (v_itr != end_v_itr){

      chain_index.erase(v_itr++);

   }


}

#ifdef DEBUG

   //zero out the contract RAM
   ACTION simplevote::clear() {

      require_auth(_self);

       while (_voters.begin() != _voters.end()) _voters.erase(_voters.begin());
       while (_chains.begin() != _chains.end()) _chains.erase(_chains.begin());

   }

#endif