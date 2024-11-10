// SPDX-License-Identifier: MIT 

pragma solidity 0.8.26; 

contract CoolNumberContract { 
    
    uint public coolNumber = 10;
    
    function setCoolNumber(uint _coolNumber) public { 
        coolNumber = _coolNumber; 
    }
} 