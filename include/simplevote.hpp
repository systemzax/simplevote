#include <eosio/eosio.hpp>
#include <eosio/symbol.hpp>


using namespace eosio;

CONTRACT simplevote : public contract {
   public:
      using contract::contract;

      struct [[eosio::table]] chain {
         
         symbol_code chain;
         name owner;

         uint64_t primary_key() const { return chain.raw(); }

      };

      struct [[eosio::table]] voter {

         name voter;
         symbol_code chain;

         uint64_t primary_key() const { return voter.value; }
         uint64_t by_chain() const { return chain.raw(); }

      };

      ACTION addchain(symbol_code chain, name owner);
      ACTION changeowner( symbol_code chain, name newowner) ;
      ACTION removechain( symbol_code chain);

      ACTION addvoter( name voter, symbol_code chain);
      ACTION removevoter( name voter);

      ACTION sendmsg( name voter, std::string message);

      #ifdef DEBUG
            ACTION clear();
      #endif
      
      typedef eosio::multi_index< "chains"_n, chain> chains;
      typedef eosio::multi_index< "voters"_n, voter,
        indexed_by<"chain"_n, const_mem_fun<voter, uint64_t, &voter::by_chain>>> voters;

      chains    _chains;
      voters   _voters;
      
      simplevote( name receiver, name code, datastream<const char*> ds ) :
         contract(receiver, code, ds),
         _chains(receiver, receiver.value),
         _voters(receiver, receiver.value)   {
         

         }



};