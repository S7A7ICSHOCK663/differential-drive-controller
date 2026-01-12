# State Diagram

IDLE --(2s timeout)--> ACTIVE  
ACTIVE --(3s timeout)--> ERROR  
ERROR --(3 blinks complete)--> IDLE
