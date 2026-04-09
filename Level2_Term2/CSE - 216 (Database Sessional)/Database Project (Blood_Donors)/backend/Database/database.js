import OracleDB from 'oracledb';
import { config } from './databaseConfiguration.js';

export async function start() {
    const pool = await OracleDB.createPool(config);
}

export async function stop(){
    await OracleDB.getPool().close(0);
}

export function queryExecute(statement, binds = [], opts = {}) {
  return new Promise(async (resolve, reject) => {
    let connection;
    let result = [];
  
    opts.outFormat = OracleDB.OBJECT;
    opts.autoCommit = true;
    // opts.resultSet = true;
  
    try {
      connection = await OracleDB.getConnection();
      result = await connection.execute(statement, binds, opts);
      resolve (result);
    } catch (err) {
      console.error(err);
      reject(err);
    } finally {
        if (connection) {
            try {
            await connection.close();
            } catch (err) {
            console.error(err);
            }
        }
    }
  });
}
  

  